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
        main.cpp
        Game.cpp
        states/StateManager.cpp
        states/State.cpp
        states/MenuState.cpp
        states/LevelState.cpp
        states/PausedState.cpp
        World.cpp
        entities/Wall.cpp
        entities/collectable/Orb.cpp
        entities/ghost/Ghost.cpp
        entities/Pacman.cpp
        Camera.cpp
        factory/EntityFactory.cpp
        factory/SFMLFactory.cpp
        views/View.cpp
        views/SFMLView.cpp
        views/SFMLWallView.cpp
        singleton/Stopwatch.cpp
        views/SFMLPacmanView.cpp
        views/collectableview/SFMLOrbView.cpp
        views/ghostview/SFMLGhostView.cpp
        views/ghostview/SFMLLockedGhostView.cpp
        views/ghostview/SFMLChaseGhostView.cpp
        views/ghostview/SFMLPredictGhost1View.cpp
        views/ghostview/SFMLPredictGhost2View.cpp
        entities/ghost/ChaseGhost.cpp
        entities/ghost/LockedGhost.cpp
        entities/ghost/PredictGhost.cpp
        singleton/Random.cpp
        Score.cpp
        sounds/WorldSound.cpp
        sounds/SFMLWorldSounds.cpp
        entities/collectable/PowerOrb.cpp
        views/collectableview/SFMLPowerOrbView.cpp
        factory/SpriteAtlas.cpp
        views/SFMLWorldView.cpp
        factory/Sprite_IDs.h
        entities/Position.h
        entities/collectable/Fruit.cpp
        views/collectableview/SFMLFruitView.cpp
        views/collectableview/SFMLFruitView.cpp)

target_link_libraries(Pacman PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)