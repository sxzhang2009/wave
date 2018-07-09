
#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#define BOOST_LOG_DYN_LINK

#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <unordered_map>

namespace wave{
  typedef std::chrono::system_clock clock;
  typedef clock::time_point time_type;

  template<class T>
  using ptr_type = boost::shared_ptr<T>;
  
  typedef long long int8;
  
  typedef std::vector<int>         vec_int;
  typedef std::vector<int8>        vec_int8;  
  typedef std::vector<bool>        vec_bool;
  typedef std::vector<float>       vec_float;
  typedef std::vector<double>      vec_double;
  typedef std::vector<std::string> vec_string;
  typedef std::vector<time_type>   vec_time;
  
  typedef ptr_type<vec_int>    vec_int_ptr;
  typedef ptr_type<vec_int8>   vec_int8_ptr;  
  typedef ptr_type<vec_bool>   vec_bool_ptr;
  typedef ptr_type<vec_float>  vec_float_ptr;
  typedef ptr_type<vec_double> vec_double_ptr;
  typedef ptr_type<vec_string> vec_string_ptr;
  typedef ptr_type<vec_time>   vec_time_ptr;

  typedef std::unordered_map<std::string,std::string> tag_values;

}

#include <boost/exception/all.hpp>

#include "error.hpp"

#define LOGIC_ERROR(x)                          \
  BOOST_THROW_EXCEPTION(wave::logic_error(x))

#define RUNTIME_ERROR(x)                        \
  BOOST_THROW_EXCEPTION(wave::runtime_error(x))

#endif
