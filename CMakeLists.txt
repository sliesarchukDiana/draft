cmake_minimum_required(VERSION 3.30)
project(laboratory)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(laboratory
        main.cpp
        movie.cpp
        movie.h
        movie.cpp
        User.cpp
        User.h
        user_manager.cpp
        user_manager.h
        comment.cpp
        comment.h
        comment_manager.cpp
        comment_manager.h
        movie_repository.cpp
        movie_repository.h
        movie_service.cpp
        movie_service.h
        movie_ui.cpp
        movie_ui.h
)
