cmake_minimum_required(VERSION 3.16.3)
project(2assignment)

set(CMAKE_CXX_STANDARD 17)

add_executable(2assignment common_threads.h fork-join.c)
