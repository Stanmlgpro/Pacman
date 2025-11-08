cmake_minimum_required(VERSION 3.28)
project(Pacman)

#set(SFML_DIR "/opt/SFML-2.6.1/lib/cmake/SFML")
set(CMAKE_CXX_FLAGS, "-Wall -Werror -fsanitize=address -g")
set(SFML_DIR "C:/Users/stan1/CLionProjects/sfml/2.6.2/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
include_directories(/opt/SFML-2.6.1/include)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Pacman
        entities/Entity.cpp
        entities/Entity.h
        main.cpp
        Game.cpp
        Game.h
        states/StateManager.cpp
        states/StateManager.h
        states/State.cpp
        states/State.h
        states/MenuState.cpp
        states/MenuState.h
        states/LevelState.cpp
        states/LevelState.h
        states/PausedState.cpp
        states/PausedState.h
        World.h
        World.cpp
        entities/Wall.cpp
        entities/Wall.h
        entities/Orb.cpp
        entities/Orb.h
        entities/Ghost.cpp
        entities/Ghost.h
        entities/Pacman.cpp
        entities/Pacman.h
        Camera.cpp
        factory/EntityFactory.h
        factory/EntityFactory.cpp
        factory/SFMLFactory.cpp
        views/View.h
        views/View.cpp
        views/SFMLView.cpp
        views/SFMLWallView.h
        views/SFMLWallView.cpp
        singleton/Stopwatch.h
        singleton/Stopwatch.cpp
        views/SFMLPacmanView.h
        views/SFMLPacmanView.cpp
        views/SFMLOrbView.h
        views/SFMLOrbView.cpp
        views/SFMLGhostView.h
        views/SFMLGhostView.cpp
        views/SFMLWallView.h)

target_link_libraries(Pacman PRIVATE sfml-graphics sfml-window sfml-system)