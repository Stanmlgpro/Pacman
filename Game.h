//
// Created by stan on 10/13/25.
//

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H
#include <memory>

#include "sounds/WorldSound.h"
#include "states/StateManager.h"

class Camera;
class EntityFactory;
class Game {
public:
    Game();

    void run();

    ~Game();
private:
    void Update() const;
    void Render();
    void CheckInput();

    std::shared_ptr<StateManager> state_manager;
    sf::RenderWindow window;
    sf::Clock time;

    std::shared_ptr<EntityFactory> entity_factory;
    std::shared_ptr<Camera> camera;

    std::shared_ptr<WorldSound> world_sound;
};


#endif //PACMAN_GAME_H