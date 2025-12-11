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
        entities/ghost/Ghost.cpp
        entities/ghost/Ghost.h
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
        views/ghostview/SFMLGhostView.h
        views/ghostview/SFMLGhostView.cpp
        views/SFMLWallView.h
        views/ghostview/SFMLLockedGhostView.h
        views/ghostview/SFMLLockedGhostView.cpp
        views/ghostview/SFMLChaseGhostView.h
        views/ghostview/SFMLChaseGhostView.cpp
        views/ghostview/SFMLPredictGhost1View.h
        views/ghostview/SFMLPredictGhost1View.cpp
        views/ghostview/SFMLPredictGhost2View.h
        views/ghostview/SFMLPredictGhost2View.cpp
        entities/ghost/ChaseGhost.h
        entities/ghost/ChaseGhost.cpp
        entities/ghost/LockedGhost.h
        entities/ghost/LockedGhost.cpp
        entities/ghost/PredictGhost.cpp
        entities/ghost/PredictGhost.h
        singleton/Random.h
        singleton/Random.cpp
        Score.h
        Score.cpp
        sounds/WorldSound.h
        sounds/WorldSound.cpp
        sounds/SFMLWorldSounds.h
        sounds/SFMLWorldSounds.cpp
        entities/PowerOrb.cpp
        views/SFMLPowerOrbView.cpp)

target_link_libraries(Pacman PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)