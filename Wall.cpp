//
// Created by stan on 10/15/25.
//

#include "Wall.h"
#include "Pacman.h"

Wall::Wall(int x, int y) {
    position.x = x;
    position.y = y;
}

std::tuple<std::shared_ptr<Entity>, bool, bool> Wall::Interact(Pacman& pacman) {
    return pacman.InteractWith(std::static_pointer_cast<Wall>(shared_from_this()));
}