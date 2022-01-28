cmake_minimum_required(VERSION 3.11)
project(parallel-maharaja)

set(CMAKE_CXX_STANDARD 17)

add_executable(parallel-maharaja main.cpp maharaja.h maharaja.cpp)
