cmake_minimum_required(VERSION 3.5)
project(nexus)

set(SRCS src/nexus.cpp)
include_directories(include)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++14)

add_executable(${PROJECT_NAME} ${SRCS})
