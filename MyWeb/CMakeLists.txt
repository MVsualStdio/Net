project(MyWeb)
set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -pthread")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
cmake_minimum_required(VERSION 3.1)

add_subdirectory(3rdparty/MyNet)

include_directories(3rdparty/MyNet/include)
include_directories(include)

file(GLOB DIR_WEB_SRCS ./src/*.cc)
message("${DIR_WEB_SRCS}")
add_library(WEBLIB ${DIR_WEB_SRCS})


set(MY_NET_LIB LOGGER THREADPOOL MYSOCKET BUFFER HTTP WEBLIB)

add_executable(web ./web.cc)
target_link_libraries(web ${MY_NET_LIB})


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
add_executable(testResponse ./test/testResponse.cc)
target_link_libraries(testResponse ${MY_NET_LIB})
