//
// Created by stan on 10/15/25.
//

#ifndef PACMAN_WALL_H
#define PACMAN_WALL_H
#include "Entity.h"

class Wall : public Entity {
public:
    Wall(int x, int y);

    ~Wall() override = default;
};


#endif //PACMAN_WALL_H