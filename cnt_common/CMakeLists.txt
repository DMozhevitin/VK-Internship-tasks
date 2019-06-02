cmake_minimum_required(VERSION 3.12)
project(work)

set(CMAKE_CXX_STANDARD 17)

add_executable(work
        gtest-all.cc
        gtest_main.cc count_common_test.cpp count_common.cpp)