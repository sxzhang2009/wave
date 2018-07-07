
#ifndef __STRATEGRY_BASE_HPP__
#define __STRATEGRY_BASE_HPP__

#include "../data/data_subscriber.hpp"

#define EXPORT_STRATEGY(name) \
  extern "C" BOOST_SYMBOL_EXPORT name strategy; \
  name strategy(#name) ;                        


namespace wave{
  namespace strategy{
    
    using namespace wave::data;
    
    class strategy_base : public data_subscriber{
    protected:
      std::string m_name;
    public:
      strategy_base(std::string t_name){
        m_name = t_name;
      }

      std::string name(){
        return m_name;
      }
      
      virtual void initialize() {};
      virtual void handle_data() {};

      // void start(){
      //   BOOST_LOG_TRIVIAL(info) << "starting strategy ";
      //   on_data();
      // };
      
      // void wait_stop(){
        
      // };
    };
  }
}



#endif
