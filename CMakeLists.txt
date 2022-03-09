cmake_minimum_required(VERSION 3.20)
project(passau_cplusplus_oop)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


add_executable(passau_cplusplus_oop
        ./question2/Student.cpp
        ./question2/Course.cpp
        ./question2/Grade.cpp
        ./question2/main.cpp)