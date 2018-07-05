
#ifndef __TICK_HPP__
#define __TICK_HPP__
#include <chrono>
#include "../common.hpp"

namespace wave{
  namespace data{
    struct tick
    {
      time_type time;
      double    price;
      long long size;
    };  
  }
}
#endif
