cmake_minimum_required (VERSION 2.6)
project (Harte_Kugeln)

list( APPEND CMAKE_CXX_FLAGS "-std=c++1y ${CMAKE_CXX_FLAGS} -Wall -g -ftest-coverage -fprofile-arcs -fmessage-length=0 ")


#use boost units for Abraham
option(USE_BOOST_UNITS "Use of boost units" ON)

configure_file (
  "${PROJECT_SOURCE_DIR}/src_sonstiges/Config.h.in"
  "${PROJECT_BINARY_DIR}/Config.h"
 )
  
include_directories ("${PROJECT_BINARY_DIR}")

include_directories ("${PROJECT_SOURCE_DIR}/cute")
add_subdirectory (cute)

include_directories ("${PROJECT_SOURCE_DIR}/src_sonstiges")
add_subdirectory (src_sonstiges)

include_directories ("${PROJECT_SOURCE_DIR}/src")
add_subdirectory (src)

include_directories ("${PROJECT_SOURCE_DIR}/unit_tests")
add_subdirectory (unit_tests)


  