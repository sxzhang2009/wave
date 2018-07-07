cmake_minimum_required (VERSION 2.6)
project (wave_test)

add_executable(unittest unittest.cpp)
target_link_libraries(unittest optimized
  wave
  boost_log_setup
  boost_log)

add_library(ema SHARED ema_break.cpp)
target_link_libraries(ema wave)

SET(CMAKE_CXX_FLAGS  "-std=c++0x" )

