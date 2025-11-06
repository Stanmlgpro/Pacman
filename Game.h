//
// Created by stan on 10/13/25.
//

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H
#include <memory>
#include "StateManager.h"

class EntityFactory;
class Game {
public:
    Game();

    void run();

    ~Game();
private:
    void Update(float dt) const;
    void Render();
    void CheckInput();

    std::shared_ptr<StateManager> state_manager;
    sf::RenderWindow window;
    sf::Clock time;

    std::shared_ptr<EntityFactory> entity_factory;
};


#endif //PACMAN_GAME_H