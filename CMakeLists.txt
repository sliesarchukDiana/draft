cmake_minimum_required(VERSION 4.0)
project(draft)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(draft
        genre.cpp
        genre.h
        main.cpp)
