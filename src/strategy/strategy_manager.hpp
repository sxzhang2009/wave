
#ifndef _STRATEGY_MANAGER_HPP__
#define _STRATEGY_MANAGER_HPP__

#include <boost/exception/all.hpp>
#include <boost/config.hpp>
#include <boost/dll/import.hpp>
#include "strategy_base.hpp"

#define BOOST_LOG_DYN_LINK

namespace wave{
  namespace strategy{
    namespace dll = boost::dll;
    class strategy_manager{
    public:
      //! run strategies 
      static int run_strategy();
    };
  }
}

#endif
