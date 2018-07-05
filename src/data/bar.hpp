
#ifndef __BAR_HPP__
#define __BAR_HPP__
#include <chrono>
#include "../common.hpp"

namespace wave{
  namespace data{
    struct bar
    {
      time_type time;
      double high;
      double low;
      double open;
      double close;
      double wap;
      int8 volume;
      int count;

      bar(time_type m_time,
              double m_open,              
              double m_high,
              double m_low,
              double m_close) :
        time(m_time),
        open(m_open),
        high(m_high),
        low(m_low),
        close(m_close),
        volume(0){
        
      }
    };
  }
}
#endif
