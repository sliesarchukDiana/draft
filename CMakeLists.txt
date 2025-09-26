cmake_minimum_required(VERSION 3.30)
project(laboratory)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(laboratory
        main.cpp
        movie.cpp
        movie.h
        movie.cpp
        movie_interface.h
)
