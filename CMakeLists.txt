cmake_minimum_required(VERSION 3.28)
project(Pacman)

#set(SFML_DIR "/opt/SFML-2.6.1/lib/cmake/SFML")
set(SFML_DIR "C:/Users/stan1/CLionProjects/sfml/2.6.2/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
include_directories(/opt/SFML-2.6.1/include)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Pacman
        Entity.cpp
        Entity.h
        main.cpp
        Game.cpp
        Game.h
        StateManager.cpp
        StateManager.h
        State.cpp
        State.h
        MenuState.cpp
        MenuState.h
        LevelState.cpp
        LevelState.h
        PausedState.cpp
        PausedState.h
        World.h
        World.cpp)

target_link_libraries(Pacman PRIVATE sfml-graphics sfml-window sfml-system)