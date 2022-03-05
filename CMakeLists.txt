cmake_minimum_required(VERSION 3.20)
project(passau_cplusplus_oop)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


add_executable(passau_cplusplus_oop
        ./question1/main.cpp)