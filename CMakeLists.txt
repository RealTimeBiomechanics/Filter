project(filter)
cmake_minimum_required(VERSION 2.8)
include_directories(lib)
if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")
endif(UNIX)
add_subdirectory(lib)
add_subdirectory(tests)

