
#include "error.hpp"

namespace wave{

  std::logic_error logic_error(std::string msg){
    return std::logic_error(msg);
  }
  
  std::logic_error logic_error(boost::format msg){
    return std::logic_error(msg.str());
  }

  std::runtime_error runtime_error(std::string msg){
    return std::runtime_error(msg);
  }
  
  std::runtime_error runtime_error(boost::format msg){
    return std::runtime_error(msg.str());
  }
}


