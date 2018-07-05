
#ifndef __DATA_SOURCE_BASE_HPP__
#define __DATA_SOURCE_BASE_HPP__

#include "tick.hpp"
#include "account.hpp"
#include "data_subscriber.hpp"

namespace wave{
  namespace data{
    
    enum DataSourceEvent {
      DS_CONNECT,
      DS_TICKDATA,
      DS_IDLE
    };

    class data_source_base {
    private:
      data_subscriber_ptr m_subscriber;
      
    public:
      void virutal connect(const tag_value& params){
        throw system_error("virutal function not implemented.");
      }

      void virutal dis_connect(const tag_value& params){
        throw system_error("virutal function not implemented.");
      }

      void virutal is_connect(const tag_value& params){
        throw system_error("virutal function not implemented.");
      }
      
      void virutal reg_bar_event(const contract& con,
              const std::string period){
        throw system_error("virutal function not implemented.");
      }

      void virtual reg_tick_event(const contract& con){
        throw system_error("virutal function not implemented.");        
      }

      contract virtual req_contract(std::string symbol){
        throw system_error("virutal function not implemented.");
      }
      
      account virtual req_account(const tag_value& params){
        throw system_error("virutal function not implemented.");        
      }
      
      void set_subscriber(data_subscriber_ptr p){
        m_subscriber = p;
      }

      void virtual stop(){
        
      }

      int8 subscribe_bar(data_subscriber* subscriber,
              contract ctr, std::string period,
              const tag_values params){
        std::vector<std::string> strs;
        boost::split(strs, period, boost::is_any_of(" "));
        int num = std::stoi(strs[0]);
        std::string unit = strs[1];
        
      }

      int8 subscribe_tick(data_subscriber* subscriber,
              contract ctr,
              const tag_values params){
        
      }
      
      void virtual event_loop(){
        throw system_error("virutal function not implemented.");
      }

    };

    typedef ptr_type<data_source_base> data_source_ptr;
    typedef std::unordered_map<std::string, data_source_ptr>
    data_source_map;
    
  }
}

#endif
