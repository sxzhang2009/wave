
#include "initialize.hpp"
#include "common.hpp"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>

namespace wave{
  void initialize(){
    //configure log output
    // boost::log::add_file_log("wave.log");
    // boost::log::core::get()->set_filter(
    //     boost::log::trivial::severity >= boost::log::trivial::info);
  }
}
