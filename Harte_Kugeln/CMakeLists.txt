cmake_minimum_required (VERSION 2.6)
project (Harte_Kugeln)

list( APPEND CMAKE_CXX_FLAGS "-std=c++1y ${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}  -g -pg -ftest-coverage -fprofile-arcs -fmessage-length=0 ")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}")

#use boost units for Abraham
option(USE_UNITS "Use of my_units" ON)

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


  