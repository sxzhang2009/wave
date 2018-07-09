
#include "../common.hpp"
#include "data_subscriber.hpp"
#include "data_source_manager.hpp"
#include "../utils.hpp"

using namespace wave;

namespace wave{
  namespace data{

    data_subscriber::data_subscriber():
      m_if_handle_data(false){
      
    }
    
    void data_subscriber::on_data_thread(){
      m_data_signal.wait();
      
      if(m_if_handle_data)
        handle_data();
    }

    void data_subscriber::update_account(){
      vec_string vs =
        data_source_manager::global()->
        available_data_sources();

      for(auto& s : vs){
        data_source_manager::global() ->
          get_data_source(s) ->
          update_account(accounts.get(s));
      }
    }
    
    int8 data_subscriber::subscribe_bar(
        const contract ctr,
        const std::string period,
        const time_type start,    
        const std::string data_source){

      BOOST_LOG_TRIVIAL(info)
        << "subscribed bar data of "
        << ctr.symbol << "with period "
        << period << " from "
        << wave::utils::strftime(start)
        << " using " << data_source;
      
      data_source_manager::global() ->
        get_data_source(data_source) ->
        subscribe_bar(m_data_signal,  ctr, period, start);
    }

    int8 data_subscriber::subscribe_tick(
        const contract ctr,
        const std::string data_source){

      BOOST_LOG_TRIVIAL(info)
        << "subscribed tick data of "
        << ctr.symbol << " from "
        << data_source;
      
      data_source_manager::global() ->
        get_data_source(data_source) ->
        subscribe_tick(m_data_signal, ctr);
    }

    time_type data_subscriber::current_time(
        const std::string data_source){
      if(data_source == ""){
        return clock::now();
      }else{
        return data_source_manager::global()->
          get_data_source(data_source) ->
          current_time();
      }
    }

    void data_subscriber::pre_initialization(){
      update_account();
    }
    
    void data_subscriber::prepare_data(){
      
    }
    
    void data_subscriber::start(){

      // start all data sources.
      data_source_manager::global() ->
        start_data_sources();

      BOOST_LOG_TRIVIAL(info) <<
        "start data subscriber event loop";

      // start data event loop thread
      m_data_thread = boost::thread(
          boost::bind(&data_subscriber::on_data_thread, this));

      BOOST_LOG_TRIVIAL(info) <<
        "call pre-initialize function";

      this->pre_initialization();

      BOOST_LOG_TRIVIAL(info) <<
        "call initialize function";
      
      // intialize strategy
      this->initialize();

      BOOST_LOG_TRIVIAL(info) <<
        "preparing data...";
      
      // prepare necessary data, e.g. historical data
      this->prepare_data();
      
      m_if_handle_data = true;
    }

    void data_subscriber::wait_stop(){
      m_data_thread.join();
    }

    void data_subscriber::send_stop_signal(){
      m_data_thread.interrupt();      
      data_source_manager::global() ->
        stop_data_sources();
    }
  }
}
