cmake_minimum_required(VERSION 3.14)
project(skip_list_implementation)

set(CMAKE_CXX_STANDARD 14)

add_executable(skip_list_implementation main.cpp Node.h SkipList.h)