cmake_minimum_required(VERSION 3.17)
project(ISP_DZ2)

set(CMAKE_CXX_STANDARD 20)

add_executable(executable main.cpp poem_sorter.cpp poem_sorter.h app_common.h my_sorts.h)

target_compile_options(executable PRIVATE -Wall -Wextra)