cmake_minimum_required (VERSION 2.6)
project (Harte_Kugeln)

list( APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -Wall -g -ftest-coverage -fprofile-arcs")

include_directories ("${PROJECT_BINARY_DIR}")

include_directories ("${PROJECT_SOURCE_DIR}/lib")
add_subdirectory (lib)

include_directories ("${PROJECT_SOURCE_DIR}/src")
add_subdirectory (src)

