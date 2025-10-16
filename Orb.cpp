//
// Created by stan on 10/15/25.
//

#include "Orb.h"

#include "Pacman.h"

Orb::Orb(int x, int y, bool big) {
    position.x = x;
    position.y = y;
    this->big = big;
}

std::tuple<std::shared_ptr<Entity>, bool, bool> Orb::Interact(Pacman& pacman) {
    pacman.InteractWith(std::static_pointer_cast<Orb>(shared_from_this()));
}

bool Orb::isBig() const {
    return big;
}