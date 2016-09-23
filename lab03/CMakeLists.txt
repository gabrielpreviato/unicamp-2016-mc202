cmake_minimum_required(VERSION 3.5.1)
project(lab03)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES main.c functions.h structures.h)
add_executable(lab03 ${SOURCE_FILES})