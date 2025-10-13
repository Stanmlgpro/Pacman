//
// Created by stan on 10/13/25.
//

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H
#include <vector>
#include "Entity.h"
#include <memory>

class Game {
public:
    Game();

    void Update(float dt);

    ~Game();
private:
    std::vector<std::shared_ptr<Entity*>> entities;
    float dt = 1;
};


#endif //PACMAN_GAME_H