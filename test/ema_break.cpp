
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
    
  }
  
  void handle_data(){
    BOOST_LOG_TRIVIAL(info) << "on_data_called.";
  }
  
};

EXPORT_STRATEGY(ema_break)
