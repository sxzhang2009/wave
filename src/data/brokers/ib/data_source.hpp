
#ifndef _DATA_SOURCE_HPP__
#define _DATA_SOURCE_HPP__

#include "../../data_source_base.hpp"
#include "../../account.hpp"
#include "../../../semaphore.hpp"
#include "../../../utils.hpp"

#include "official/EWrapper.h"
#include "official/EReaderOSSignal.h"
#include "official/EReader.h"
#include "official/EClientSocket.h"
#include "official/EPosixClientSocketPlatform.h"

#include <memory>
#include <vector>
#include <boost/log/trivial.hpp>

namespace wave{
  namespace data{
    namespace ib{

      // class EClientSocket;
      using namespace wave::data;
      using namespace wave;
      
      class data_source : public EWrapper, public data_source_base
      {
        EClientSocket* m_client;
        EReaderOSSignal m_signal;
        EReader *m_pReader;
        tag_values m_tv;
        EReader* m_reader;

        semaphore m_req_current_time_signal;
        time_type m_current_time;

        semaphore m_req_account_summary_signal;
        account_summary m_account_summary;
        int m_num_account_summary_response;
        
      public:

        data_source(std::string t_name, tag_values& t_configs);
        
        ~data_source(){};

        void set_connect_options(const std::string&);

        void connect() override ;
        
        void disconnect() override ;
        
        bool is_connected() const override ;

        void start() override;

        void clean() override;

        time_type current_time() override;
        
        void process_msgs() override;

        void update_account(account& acc) override;
        
        // account& get_account() override;
        
        // contract req_contract(std::string symbol) override;

        // account req_account(const tag_values& params) override;

        // void event_loop() override;

      private:
        // void pnlOperation();
        // void pnlSingleOperation();
        // void tickDataOperation();
        // void tickOptionComputationOperation();
        // void delayedTickDataOperation();
        // void marketDepthOperations();
        // void realTimeBars();
        // void marketDataType();
        // void historicalDataRequests();
        // void optionsOperations();
        // void accountOperations();
        // void orderOperations();
        // void ocaSamples();
        // void conditionSamples();
        // void bracketSample();
        // void hedgeSample();
        // void contractOperations();
        // void marketScanners();
        // void reutersFundamentals();
        // void bulletins();
        // void testAlgoSamples();
        // void financialAdvisorOrderSamples();
        // void financialAdvisorOperations();
        // void testDisplayGroups();
        // void miscelaneous();
        // void reqFamilyCodes();
        // void reqMatchingSymbols();
        // void reqMktDepthExchanges();
        // void reqNewsTicks();
        // void reqSmartComponents();
        // void reqNewsProviders();
        // void reqNewsArticle();
        // void reqHistoricalNews();
        // void reqHeadTimestamp();
        // void reqHistogramData();
        // void rerouteCFDOperations();
        // void marketRuleOperations();
        // void continuousFuturesOperations();
        // void reqHistoricalTicks();
        // void reqTickByTickData();
        // void whatIfSamples();
        // void reqCurrentTime();

      public:
        // events
#include "official/EWrapper_prototypes.h"

      private:
        // void printContractMsg(const Contract& contract);
        // void printContractDetailsMsg(const ContractDetails& contractDetails);
        // void printContractDetailsSecIdList(const TagValueListSPtr &secIdList);
        // void printBondContractDetailsMsg(const ContractDetails& contractDetails);

      };
    }
  }
}

#endif

