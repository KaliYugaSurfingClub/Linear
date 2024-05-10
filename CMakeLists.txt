cmake_minimum_required(VERSION 3.28)
project(liner_algebra)

set(CMAKE_CXX_STANDARD 20)

include_directories(includes/)

add_executable(liner_algebra main.cpp
        Std.cpp)
