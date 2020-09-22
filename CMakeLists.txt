cmake_minimum_required(VERSION 3.17)
project(OSLabs)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(OSLabs
        Lab1/Allocator.cpp
        Lab1/Allocator.h
        Lab1/main.cpp)
