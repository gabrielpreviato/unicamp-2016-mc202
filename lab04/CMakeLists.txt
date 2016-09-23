cmake_minimum_required(VERSION 3.5.1)
project(lab04)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic -lm")

set(SOURCE_FILES main.c dynamic_vector.c dynamic_vector.h)
add_executable(lab03 ${SOURCE_FILES})