
#pragma once
#ifndef testcppclient_h__INCLUDED
#define testcppclient_h__INCLUDED

#include "official/EWrapper.h"
#include "official/EReaderOSSignal.h"
#include "official/EReader.h"

#include <memory>
#include <vector>
#include <boost/log/trivial.hpp>

namespace wave{
  namespace data{
    namespace ib{

      class EClientSocket;

      class data_source : public EWrapper, data_source_base
      {
        EClientSocket* m_client;
        EReaderOSSignal m_signal;
        EReader *m_pReader;
        tag_values m_tv;
      public:

        data_source();
        ~data_source();

        void set_connect_options(const std::string&);
        void process_msg();

      public:

        data_source(tag_values& tv) :
          m_client(new EClientSocket(this, &m_signal)),
          m_tv(tv){
        }
        
        void connect() override {

          using namespace std;
          string host = m_tv["host"];
          int port = std::stoi(m_tv["port"]);
          int client_id = std::stoi(m_tv["client_id"]);
          
          BOOST_LOG_TRIVIAL(info) << "Connecting to " << host
                                  << ":"<< port << " with client_id = "
                                  << client_id  << std::endl;
          bool bres =
            m_client->eConnect(host, port, clientId, false);
	
          if (bres) {
            BOOST_LOG_TRIVIAL(info) << "Connected to " << host
                                    << ":"<< port <<" with client_id = "
                                    << client_id  << std::endl;
            
            m_reader = new EReader(m_client, &m_signal);
            m_reader->start();
          } else {
            throw runtime_error("can not connect to data source.\n");
          }
        };
        
        void disconnect() const override;
        
        bool is_connected() const override;
        
        // contract req_contract(std::string symbol) override;

        // account req_account(const tag_values& params) override;

        // void event_loop() override;

      private:
        void pnlOperation();
        void pnlSingleOperation();
        void tickDataOperation();
        void tickOptionComputationOperation();
        void delayedTickDataOperation();
        void marketDepthOperations();
        void realTimeBars();
        void marketDataType();
        void historicalDataRequests();
        void optionsOperations();
        void accountOperations();
        void orderOperations();
        void ocaSamples();
        void conditionSamples();
        void bracketSample();
        void hedgeSample();
        void contractOperations();
        void marketScanners();
        void reutersFundamentals();
        void bulletins();
        void testAlgoSamples();
        void financialAdvisorOrderSamples();
        void financialAdvisorOperations();
        void testDisplayGroups();
        void miscelaneous();
        void reqFamilyCodes();
        void reqMatchingSymbols();
        void reqMktDepthExchanges();
        void reqNewsTicks();
        void reqSmartComponents();
        void reqNewsProviders();
        void reqNewsArticle();
        void reqHistoricalNews();
        void reqHeadTimestamp();
        void reqHistogramData();
        void rerouteCFDOperations();
        void marketRuleOperations();
        void continuousFuturesOperations();
        void reqHistoricalTicks();
        void reqTickByTickData();
        void whatIfSamples();

        void reqCurrentTime();

      public:
        // events
#include "EWrapper_prototypes.h"


      private:
        void printContractMsg(const Contract& contract);
        void printContractDetailsMsg(const ContractDetails& contractDetails);
        void printContractDetailsSecIdList(const TagValueListSPtr &secIdList);
        void printBondContractDetailsMsg(const ContractDetails& contractDetails);

      };
    }
  }
}
#endif

