
#ifndef _DATA_SOURCE_HPP__
#define _DATA_SOURCE_HPP__

#include "../../data_source_base.hpp"
#include "../../account.hpp"

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
      class data_source : public EWrapper, public data_source_base
      {
        EClientSocket* m_client;
        EReaderOSSignal m_signal;
        EReader *m_pReader;
        tag_values m_tv;
        EReader* m_reader;
        
      public:

        data_source();
        data_source(tag_values& tv);
        
        ~data_source(){};

        void set_connect_options(const std::string&);

        
        void connect() override ;
        
        void disconnect() override ;
        
        bool is_connected() const override ;

        void start() override;

        void clean() override;

        void process_msgs() override;
        
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

