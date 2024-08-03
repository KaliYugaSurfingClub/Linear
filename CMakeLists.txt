cmake_minimum_required(VERSION 3.28)
project(linear_algebra)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(includes)

add_executable(linear_algebra main.cpp)
