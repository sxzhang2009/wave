
#include "data_source.hpp"
#include <iostream>
#include "official/AccountSummaryTags.hpp"
#include <boost/thread.hpp>

namespace wave{
  namespace data{
    namespace ib{
      using namespace wave::data;
      
      data_source::data_source(
          const std::string t_name,
          tag_values& t_configs):
        data_source_base(t_name, t_configs),
        m_client(new EClientSocket(this, &m_signal)){
      }

      void data_source::connect() {
        using namespace std;
        string host = m_configs["host"];
        int port = std::stoi(m_configs["port"]);
        int client_id = 1;

        tag_values::iterator it = m_configs.find("client_id");
        
        if(it != m_configs.end())
          client_id = std::stoi(it->second);
          
        BOOST_LOG_TRIVIAL(info) << "connecting to " << host
                                << ":"<< port << " with client_id = "
                                << client_id;
        bool bres =
          m_client->eConnect(host.c_str(), port, client_id, false);
	
        if (bres) {
          BOOST_LOG_TRIVIAL(info) << "connected to " << host
                                  << ":"<< port <<" with client_id = "
                                  << client_id;
            
          m_reader = new EReader(m_client, &m_signal);
          m_reader->start();
        } else {
          RUNTIME_ERROR("can not connect to data source.\n");
        }
      }

      void data_source::disconnect() {
        m_client->eDisconnect();
      };

      bool data_source::is_connected() const {
        m_client->isConnected();
      };

      void data_source::start() {
        this->connect();
        process_msgs();
      }

      void data_source::clean(){
        this->disconnect();
      }
      
      void data_source::process_msgs() {
        while(true){
          boost::this_thread::interruption_point();
          m_signal.waitForSignal();
          errno = 0;
          m_reader->processMsgs();
        }
      }

      time_type data_source::current_time(){
        m_client->reqCurrentTime();
        m_req_current_time_signal.wait();
        return m_current_time;
      }
      
      void data_source::update_account(account& acc){
        
        m_num_account_summary_response =
          AccountSummaryTags::get()->getNumTags();
        
        m_client->reqAccountSummary(9001, "All",
                AccountSummaryTags::get()->getAllTags());
        
        m_req_account_summary_signal.wait();

        //! fill account structure
        account_summary::iterator it;
        
        it = m_account_summary.find("AccountType");
        if(it != m_account_summary.end()){
          acc.name = it->second;
        }

        it = m_account_summary.find("NetLiquidation");
        if(it != m_account_summary.end()){
          acc.net_value = std::stod(it->second);
        }

        it = m_account_summary.find("TotalCashValue");
        if(it != m_account_summary.end()){
          acc.total_cash = std::stod(it->second);
        }

        it = m_account_summary.find("SettledCash");
        if(it != m_account_summary.end()){
          acc.settled_cash = std::stod(it->second);
        }

        it = m_account_summary.find("AccruedCash");
        if(it != m_account_summary.end()){
          acc.accrued_cash = std::stod(it->second);
        }

        it = m_account_summary.find("BuyingPower");
        if(it != m_account_summary.end()){
          acc.buying_power = std::stod(it->second);
        }

        it = m_account_summary.find("EquityWithLoanValue");
        if(it != m_account_summary.end()){
          acc.equity_with_load = std::stod(it->second);
        }

        it = m_account_summary.find("PreviousEquityWithLoanValue");
        if(it != m_account_summary.end()){
          acc.previous_equity_with_load = std::stod(it->second);
        }

        it = m_account_summary.find("GrossPositionValue");
        if(it != m_account_summary.end()){
          acc.gross_possition_value = std::stod(it->second);
        }

        it = m_account_summary.find("ReqTEquity");
        if(it != m_account_summary.end()){
          acc.reqt_equity = std::stod(it->second);
        }

        it = m_account_summary.find("ReqTMargin");
        if(it != m_account_summary.end()){
          acc.reqt_margin = std::stod(it->second);
        }
        
        it = m_account_summary.find("SMA");
        if(it != m_account_summary.end()){
          acc.sma = std::stod(it->second);
        }

        it = m_account_summary.find("InitMarginReq");
        if(it != m_account_summary.end()){
          acc.init_margin_req = std::stod(it->second);
        }
        
        it = m_account_summary.find("MaintMarginReq");
        if(it != m_account_summary.end()){
          acc.maint_margin_req = std::stod(it->second);
        }

        it = m_account_summary.find("AvailableFunds");
        if(it != m_account_summary.end()){
          acc.available_funds = std::stod(it->second);
        }

        it = m_account_summary.find("ExcessLiquidity");
        if(it != m_account_summary.end()){
          acc.excess_liquidity = std::stod(it->second);
        }

        it = m_account_summary.find("Cushion");
        if(it != m_account_summary.end()){
          acc.cushion = std::stod(it->second);
        }

        it = m_account_summary.find("DayTradesRemaining");
        if(it != m_account_summary.end()){
          acc.day_trade_remaining = std::stod(it->second);
        }

        it = m_account_summary.find("Leverage");
        if(it != m_account_summary.end()){
          acc.leverage = std::stod(it->second);
        }

      };

      //////////////////////////////////////
      void data_source::tickPrice(TickerId tickerId, TickType field,
              double price, const TickAttrib& attrib){};
      
      void data_source::tickSize(TickerId tickerId,
              TickType field, int size){};
      
      void data_source::tickOptionComputation(TickerId tickerId,
              TickType tickType, double impliedVol, double delta,
              double optPrice, double pvDividend, double gamma,
              double vega, double theta, double undPrice){};
      
      void data_source::tickGeneric(TickerId tickerId,
              TickType tickType, double value){};
      
      void data_source::tickString(TickerId tickerId,
              TickType tickType, const string& value){};
      
      void data_source::tickEFP(TickerId tickerId,
              TickType tickType, double basisPoints,
              const string& formattedBasisPoints,
              double totalDividends, int holdDays,
              const string& futureLastTradeDate,
              double dividendImpact, double dividendsToLastTradeDate){};
      
      void data_source::orderStatus(OrderId orderId,
              const string& status, double filled,
              double remaining, double avgFillPrice,
              int permId, int parentId,
              double lastFillPrice, int clientId,
              const string& whyHeld, double mktCapPrice){};
      
      void data_source::openOrder(OrderId orderId,
              const Contract&, const Order&, const OrderState&){};
      
      void data_source::openOrderEnd(){};
      
      void data_source::winError(const string& str,
              int lastError){};
      
      void data_source::connectionClosed(){};
      
      void data_source::updateAccountValue(const string& key,
              const string& val,
              const string& currency,
              const string& accountName){};
      
      void data_source::updatePortfolio(const Contract& contract,
              double position,
              double marketPrice,
              double marketValue,
              double averageCost,
              double unrealizedPNL,
              double realizedPNL,
              const string& accountName){};
      
      void data_source::updateAccountTime(const string& timeStamp){};
      
      void data_source::accountDownloadEnd(const string& accountName){};

      void data_source::nextValidId(OrderId orderId){
        std::cout<<"order Id = "<< orderId << std::endl;
        // m_client->reqAccountSummary(9001, "All",
        //         AccountSummaryTags::getAllTags());
      };
      
      void data_source::contractDetails(int reqId,
              const ContractDetails& contractDetails){
        
      };
      
      void data_source::bondContractDetails(int reqId,
              const ContractDetails& contractDetails){};
      
      void data_source::contractDetailsEnd(int reqId){};
      
      void data_source::execDetails(int reqId,
              const Contract& contract, const Execution& execution){};
      
      void data_source::execDetailsEnd(int reqId){};
      
      void data_source::error(int id, int errorCode,
              const string& errorString){};
      
      void data_source::updateMktDepth(TickerId id,
              int position, int operation, int side,
              double price, int size){};
      
      void data_source::updateMktDepthL2(TickerId id,
              int position, const string& marketMaker, int operation,
              int side, double price, int size){};
      
      void data_source::updateNewsBulletin(int msgId,
              int msgType, const string& newsMessage,
              const string& originExch){};
      
      void data_source::managedAccounts(const string& accountsList){};
      
      void data_source::receiveFA(faDataType pFaDataType,
              const string& cxml){};
      
      void data_source::historicalData(TickerId reqId, const Bar& bar){};
      
      void data_source::historicalDataEnd(int reqId,
              const string& startDateStr, const string& endDateStr){};
      
      void data_source::scannerParameters(const string& xml){};
      
      void data_source::scannerData(int reqId, int rank,
              const ContractDetails& contractDetails,
              const string& distance, const string& benchmark,
              const string& projection,
              const string& legsStr){};
      
      void data_source::scannerDataEnd(int reqId){};
      
      void data_source::realtimeBar(TickerId reqId, long time,
              double open, double high, double low, double close,
              long volume, double wap, int count){};
      
      void data_source::currentTime(long time){
        m_current_time =
          wave::utils::intptime((int8)time*1E6);
        m_req_current_time_signal.notify();
      };
      
      void data_source::fundamentalData(TickerId reqId,
              const string& data){};
      
      void data_source::deltaNeutralValidation(int reqId,
              const DeltaNeutralContract& deltaNeutralContract){};
      
      void data_source::tickSnapshotEnd(int reqId){};
      
      void data_source::marketDataType(TickerId reqId, int marketDataType){};
      
      void data_source::commissionReport(
          const CommissionReport& commissionReport){};
      
      void data_source::position(const string& account,
              const Contract& contract, double position, double avgCost){};
      
      void data_source::positionEnd(){};

      void data_source::accountSummary(int reqId, const string& account,
              const string& tag, const string& value, const string& curency){

        // m_account_summary["tag"] = value;
        m_account_summary[tag] = value;
        
        m_num_account_summary_response--;

        // std::cout<<tag <<" : "
        //          << value << " "
        //          <<m_num_account_summary_response
        //          <<std::endl;
        
        if(m_num_account_summary_response <= 0){
          m_req_account_summary_signal.notify();
        }
          
        // std::cout<< " redId = " << reqId
        //          << " account = " << account
        //          << " tag = " << tag
        //          << " value = " << value
        //          << " curency = " << curency
        //          << std::endl;
        
      };
      
      void data_source::accountSummaryEnd(int reqId){};
      
      void data_source::verifyMessageAPI(const string& apiData){};
      
      void data_source::verifyCompleted(bool isSuccessful,
              const string& errorText){};
      
      void data_source::displayGroupList(int reqId, const string& groups){};
      
      void data_source::displayGroupUpdated(int reqId,
              const string& contractInfo){};
      
      void data_source::verifyAndAuthMessageAPI(const string& apiData,
              const string& xyzChallange){};
      
      void data_source::verifyAndAuthCompleted(bool isSuccessful,
              const string& errorText){};
      
      void data_source::connectAck(){};
      
      void data_source::positionMulti(int reqId, const string& account,
              const string& modelCode, const Contract& contract,
              double pos, double avgCost){};
      
      void data_source::positionMultiEnd(int reqId){};
      
      void data_source::accountUpdateMulti(int reqId, const string& account,
              const string& modelCode, const string& key,
              const string& value, const string& currency){};
      
      void data_source::accountUpdateMultiEnd(int reqId){};
      
      void data_source::securityDefinitionOptionalParameter(
          int reqId, const string& exchange, int underlyingConId,
          const string& tradingClass,
          const string& multiplier,
          const std::set< string>& expirations,
          const std::set<double>& strikes){};
      
      void data_source::securityDefinitionOptionalParameterEnd(int reqId){};
      
      void data_source::softDollarTiers(int reqId,
              const std::vector<SoftDollarTier> &tiers){};
      
      void data_source::familyCodes(
          const std::vector<FamilyCode> &familyCodes){};
      
      void data_source::symbolSamples(int reqId,
              const std::vector<ContractDescription> &contractDescriptions){};
      
      void data_source::mktDepthExchanges(
          const std::vector<DepthMktDataDescription> &
          depthMktDataDescriptions){};
      
      void data_source::tickNews(int tickerId, time_t timeStamp,
              const string& providerCode,
              const string& articleId,
              const string& headline, const string& extraData){};
      
      void data_source::smartComponents(int reqId,
              const SmartComponentsMap& theMap){};
      
      void data_source::tickReqParams(int tickerId, double minTick,
              const string& bboExchange, int snapshotPermissions){};
      
      void data_source::newsProviders(const std::vector<NewsProvider> &newsProviders){};
      
      void data_source::newsArticle(int requestId, int articleType,
              const string& articleText){};
      
      void data_source::historicalNews(int requestId, const string& time,
              const string& providerCode, const string& articleId, const string& headline){};
      
      void data_source::historicalNewsEnd(int requestId, bool hasMore){};
      
      void data_source::headTimestamp(int reqId, const string& headTimestamp){};
      
      void data_source::histogramData(int reqId, const HistogramDataVector& data){};
      
      void data_source::historicalDataUpdate(TickerId reqId, const Bar& bar){};
      
      void data_source::rerouteMktDataReq(int reqId, int conid, const string& exchange){};
      
      void data_source::rerouteMktDepthReq(int reqId, int conid, const string& exchange){};
      
      void data_source::marketRule(int marketRuleId,
              const std::vector<PriceIncrement> &priceIncrements){};
      
      void data_source::pnl(int reqId, double dailyPnL,
              double unrealizedPnL, double realizedPnL){};
      
      void data_source::pnlSingle(int reqId, int pos, double dailyPnL,
              double unrealizedPnL, double realizedPnL, double value){};
      
      void data_source::historicalTicks(int reqId,
              const std::vector<HistoricalTick> &ticks, bool done){};
      
      void data_source::historicalTicksBidAsk(int reqId,
              const std::vector<HistoricalTickBidAsk> &ticks, bool done){};
      
      void data_source::historicalTicksLast(int reqId,
              const std::vector<HistoricalTickLast> &ticks, bool done){};
      
      void data_source::tickByTickAllLast(int reqId, int tickType,
              time_t time, double price, int size,
              const TickAttrib& attribs, const string& exchange,
              const string& specialConditions){};
      
      void data_source::tickByTickBidAsk(int reqId, time_t time,
              double bidPrice, double askPrice, int bidSize,
              int askSize, const TickAttrib& attribs){};
      
      void data_source::tickByTickMidPoint(int reqId, time_t time,
              double midPoint){};

      
    }
  }
}
