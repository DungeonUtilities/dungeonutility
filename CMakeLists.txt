cmake_minimum_required(VERSION 3.3)
project(dungeonutility)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES test.cpp dice.h test.cpp)
add_executable(dungeonutility ${SOURCE_FILES} dice.h main.cpp)