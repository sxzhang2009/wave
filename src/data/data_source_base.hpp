
#ifndef __DATA_SOURCE_BASE_HPP__
#define __DATA_SOURCE_BASE_HPP__

#include "tick.hpp"
#include "account.hpp"
#include "contract.hpp"
#include "../semaphore.hpp"

namespace wave{
  namespace data{

    enum DataSourceEvent {
      DS_CONNECT,
      DS_TICKDATA,
      DS_IDLE
    };

    class data_source_base {
    private:
      account m_account;
    public:

      //! connect to data source.
      virtual void connect() = 0;

      //! disconnect to data source.
      virtual void disconnect() = 0;

      //! check if connection is established.
      virtual bool is_connected() const = 0;

      //! start this data source
      virtual void start() = 0;

      //! clean resources. e.g. disconnect data source
      virtual void clean() = 0;

      // //! 
      // virtual void reg_bar_event(const contract& con,
      //         const std::string period) = 0;


      // virtual void reg_tick_event(const contract& con){
      //   throw logic_error("virutal function not implemented.");        
      // }

      // virtual contract req_contract(std::string symbol) = 0;

      
      // virtual void req_account_summary(
      //     account& account_summary,
      //     wave::semaphore& sem){
      //   throw logic_error("virutal function not implemented.");        
      // }

      // virtual void stop(){
        
      // }

      int8 subscribe_bar(
          wave::semaphore& bar_signal,
          const contract ctr,
          const std::string period,
          const time_type start){
        
        // std::vector<std::string> strs;
        // boost::split(strs, period, boost::is_any_of(" "));
        // int num = std::stoi(strs[0]);
        // std::string unit = strs[1];
        return 0;
      }

      int8 subscribe_tick(
          wave::semaphore& tick_singal,          
          contract ctr){
        return 0;
      }

      virtual ~data_source_base(){
        
      }

      virtual void process_msgs() = 0;
    };

    typedef ptr_type<data_source_base> data_source_ptr;
    typedef std::unordered_map<std::string, data_source_ptr> data_source_map;
  }
}


#endif
