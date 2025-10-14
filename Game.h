//
// Created by stan on 10/13/25.
//

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H
#include <vector>
#include "Entity.h"
#include <memory>
#include <SFML/Graphics.hpp>

#include "StateManager.h"

class Game {
public:
    Game();

    void run();
    void Update(float dt);
    void render();

    ~Game();
private:
    std::unique_ptr<StateManager*> Statemanager;
    sf::RenderWindow* window;
    float dt = 1;
};


#endif //PACMAN_GAME_H