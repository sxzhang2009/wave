
#ifndef __DATA_SUBSCRIBER_HPP__
#define __DATA_SUBSCRIBER_HPP__

#include "data_source_base.hpp"
#include "../common.hpp"
#include "data_source_manager.hpp"

namespace wave{
  namespace data{
    // create a thread for each data source.
    class data_subscriber {
    private:
      data_source_manager m_ds_manager;
      void init_data_sources();
      void start_data_sources();
      void feed_tick(wave::data::tick& t);
      void event_loop();
      void on_data();

    protect:

      //! an event function raised by data_source
      void virtual on_data(){}
      
      tick& tick(int8 id){
        
      }

      bar& bar(int8 id){
        
      }
      
      //! subscribe the bar data.
      //! symbols are of format like "US/AAPL",
      //! where 'US' represents the country and 'AAPL'
      //! is the stock symbol.
      int8 subscribe_bar(const contract ctr,
              const std::string period,
              const std::string data_source,
              const tag_values params){
        m_ds_manager.get_data_source(data_source) ->
          subscribe_bar(this, ctr, period);
      };

      int8 subscribe_tick(const contract ctr,
              const std::string data_source,
              const tag_values params){
        m_ds_manager.get_data_source(data_source) ->
          subscribe_tick(this, ctr);
      };

    public:
      data_subscriber(){
        
      }
      
      void req_hist_bar(std::string symbol,
              std::string type,
              wave::time_type from,
              wave::time_type to);


    };

    typedef ptr_type<data_subscriber> data_subscriber_ptr;
  }
}
#endif
