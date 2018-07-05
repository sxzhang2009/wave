
#ifndef __DATE_HPP__
#define __DATE_HPP__

#include "common.hpp"
#include "date/date.h"


namespace wave{
  namespace utils{

    //! convert time_type to string
    std::string strftime(time_type t);

    //! parse string to time_type
    time_type strptime(std::string s);

    //! convert int8 (microseconds) to time
    time_type intptime(int8 i);
    
  }
}

#endif
