cmake_minimum_required(VERSION 3.5)
project(iris)

set(SRCS src/iris.cpp include/iris.h)
include_directories(include)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++1z)
add_executable(${PROJECT_NAME} ${SRCS})
