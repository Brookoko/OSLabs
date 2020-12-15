cmake_minimum_required(VERSION 3.17)
project(OSLabs)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(OSLabs
        Lab1/Allocator.cpp Lab1/Allocator.h
        Lab2/PageAllocator.h Lab2/PageAllocator.cpp
        lab4/Job.h lab4/hungarian.h
        lab4/main.cpp)
