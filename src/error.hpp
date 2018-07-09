
#ifndef __ERROR_HPP__
#define __ERROR_HPP__

#include <stdexcept>
#include <boost/format.hpp>

namespace wave{
  std::logic_error logic_error(std::string msg);
  std::logic_error logic_error(boost::format msg);

  std::runtime_error runtime_error(std::string msg);
  std::runtime_error runtime_error(boost::format msg);
}

#endif
