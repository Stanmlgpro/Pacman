//
// Created by stan on 10/13/25.
//

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H
#include <vector>
#include "Entity.h"
#include <memory>

#include "StateManager.h"

class Game {
public:
    Game();

    void Update(float dt);

    ~Game();
private:
    std::unique_ptr<StateManager*> StateManager;
    float dt = 1;
};


#endif //PACMAN_GAME_H