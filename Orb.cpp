//
// Created by stan on 10/15/25.
//

#include "Orb.h"

#include "Pacman.h"

Orb::Orb(float x, float y, bool big) {
    position.x = x;
    position.y = y;
    this->big = big;
}

std::tuple<std::shared_ptr<Entity>, bool, bool> Orb::Interact(Pacman& pacman) {
    return pacman.InteractWith(std::static_pointer_cast<Orb>(shared_from_this()));
}

bool Orb::isBig() const {
    return big;
}