
#include "utils.hpp"
#include <sstream>

namespace wave{
  namespace utils{

    std::string strftime(time_type t){
      using namespace std::chrono;
      return date::format("%F %T",
              time_point_cast<microseconds>(t));
    }
  
    time_type strptime(std::string s){
      time_type tp;
      std::istringstream(s) >> date::parse("%F %TZ", tp);
      return tp;
    }

    time_type intptime(long long i){
      using namespace std::chrono;
      std::time_t sec = std::time_t(i / 1000000);
      auto sec_tp = system_clock::from_time_t(sec);
      auto us = microseconds(i % 1000000);
      return sec_tp + us;
    }
  }
}

