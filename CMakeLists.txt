
project(MyNet)
set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -pthread")

cmake_minimum_required(VERSION 3.1)
MESSAGE(STATUS "build start")

include_directories(include)

add_subdirectory(include)
set(NET_LIB LOGGER THREADPOOL MYSOCKET BUFFER)
add_subdirectory(test)

