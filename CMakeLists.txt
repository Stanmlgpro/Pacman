cmake_minimum_required(VERSION 3.28)
project(Pacman)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Pacman
        Entity.cpp
        Entity.h
        main.cpp
        Game.cpp
        Game.h
        StateManager.cpp
        StateManager.h)
