//
// Created by stan on 10/15/25.
//

#ifndef PACMAN_WALL_H
#define PACMAN_WALL_H
#include "Entity.h"

class Wall : public Entity, public std::enable_shared_from_this<Wall> {
public:
    Wall(float x, float y);

    std::tuple<std::shared_ptr<Entity>, bool, bool> Interact(Pacman& pacman) override;

    ~Wall() override = default;
};


#endif //PACMAN_WALL_H