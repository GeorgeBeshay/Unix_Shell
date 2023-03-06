cmake_minimum_required(VERSION 3.24)
project(src)

set(CMAKE_CXX_STANDARD 17)

add_executable(src main.c main.h strings_utilities.c strings_utilities.h colors.h)
