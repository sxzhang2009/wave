
#ifndef __DATA_SUBSCRIBER_HPP__
#define __DATA_SUBSCRIBER_HPP__

#include "../common.hpp"
#include "../semaphore.hpp"

#include "contract.hpp"
#include "tick.hpp"
#include "data_source_base.hpp"
#include <boost/thread.hpp>

namespace wave{
  namespace data{
    // create a thread for each data source.
    class data_subscriber {
    private:
      bool m_if_handle_data;
      
      void on_data_thread();

      wave::semaphore m_data_signal;
      boost::thread m_data_thread;

      //! called after data source started
      //! but before initialization function.
      void pre_initialization();
      
      //! prepare necessary data, e.g. historical data
      //! according to the data subscription
      void prepare_data();

    protected:
      account_map accounts;
      
    protected:
      virtual void initialize() = 0;
      virtual void handle_data() = 0;

      //! get current time from local or from data_source.
      virtual time_type current_time(
          const std::string data_source = "");

      virtual void update_account();
      
      //! an event function raised by data_source
      
      // tick& get_tick(int8 id){
        
      // }

      // bar& get_bar(int8 id){
        
      // }

      
      //! subscribe the bar data.
      //! symbols are of format like "US/AAPL",
      //! where 'US' represents the country and 'AAPL'
      //! is the stock symbol.
      int8 subscribe_bar(const contract ctr,
              const std::string period,
              const time_type start,
              const std::string data_source);

      int8 subscribe_tick(const contract ctr,
              const std::string data_source);

      
    public:

      data_subscriber();
      
      //! start data soruces and data event loop
      virtual void start();
      
      virtual void wait_stop();

      virtual void send_stop_signal();
      
      void req_hist_bar(std::string symbol,
              std::string type,
              wave::time_type from,
              wave::time_type to);


    };

    typedef ptr_type<data_subscriber> data_subscriber_ptr;
  }
}
#endif
