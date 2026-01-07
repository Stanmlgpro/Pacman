cmake_minimum_required(VERSION 3.28)
project(Pacman)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_library(pacman_core
        entities/Entity.cpp
        World.cpp
        entities/Wall.cpp
        entities/collectable/Orb.cpp
        entities/ghost/Ghost.cpp
        entities/Pacman.cpp
        Camera.cpp
        singleton/Stopwatch.cpp
        entities/ghost/ChaseGhost.cpp
        entities/ghost/LockedGhost.cpp
        entities/ghost/PredictGhost.cpp
        singleton/Random.cpp
        Score.cpp
        sounds/WorldSound.cpp
        entities/collectable/PowerOrb.cpp
        entities/collectable/Fruit.cpp
        factory/EntityFactory.cpp
)

add_library(pacman_sfml
        Game.cpp
        states/StateManager.cpp
        states/State.cpp
        states/MenuState.cpp
        states/LevelState.cpp
        states/PausedState.cpp
        factory/SFMLFactory.cpp
        factory/SpriteAtlas.cpp
        views/View.cpp
        views/SFMLView.cpp
        views/SFMLWallView.cpp
        views/SFMLPacmanView.cpp
        views/collectableview/SFMLOrbView.cpp
        views/ghostview/SFMLGhostView.cpp
        views/ghostview/SFMLLockedGhostView.cpp
        views/ghostview/SFMLChaseGhostView.cpp
        views/ghostview/SFMLPredictGhost1View.cpp
        views/ghostview/SFMLPredictGhost2View.cpp
        views/collectableview/SFMLPowerOrbView.cpp
        views/SFMLWorldView.cpp
        views/collectableview/SFMLFruitView.cpp
        sounds/SFMLWorldSounds.cpp
)

target_include_directories(pacman_core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(pacman_sfml PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Pacman main.cpp)

target_link_libraries(pacman_sfml PUBLIC pacman_core sfml-graphics sfml-window sfml-system sfml-audio)
target_link_libraries(Pacman PRIVATE pacman_sfml)