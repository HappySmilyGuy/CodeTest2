cmake_minimum_required(VERSION 3.6)
project(Rubiks_Cube)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp headers/Cube.h src/Cube.cpp)
add_executable(Rubiks_Cube ${SOURCE_FILES})