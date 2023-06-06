cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(File2Header)

add_executable(
    file2header file2header.cpp
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build" FORCE)
endif()
