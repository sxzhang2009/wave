
#include "../src/wave.hpp"
#include <iostream>

using namespace wave::strategy;

class ema_break : public strategy_base{
private:
  //define private variables here
  
public:
  
  ema_break(std::string t_name):
    strategy_base(t_name){}
  
  void initialize(){
    BOOST_LOG_TRIVIAL(info)
      << "current time is :"
      << wave::utils::strftime(current_time());

    BOOST_LOG_TRIVIAL(info)
      << "current time from data source is :"
      << wave::utils::strftime(current_time("ib-data"));

    std::cout<<"net value is "
             << accounts["ib-data"].net_value;
  }
  
  void handle_data(){
    BOOST_LOG_TRIVIAL(info) << "on_data_called.";
  }
  
};

EXPORT_STRATEGY(ema_break)
