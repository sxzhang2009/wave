
#ifndef __ACCOUNT_HPP__
#define __ACCOUNT_HPP__

// #include "TagValue.h"
#include "../common.hpp"
#include <boost/any.hpp>

namespace wave{
  namespace data{
    using namespace std;

    // typedef std::unordered_map<std::string, boost::any>
    typedef std::unordered_map<std::string, boost::any>
    account;
    
  }
}

#endif
