//
// Created by stan on 10/15/25.
//

#include "Orb.h"
#include "Pacman.h"
#include "World.h"
#include <iostream>

Orb::Orb(float x, float y, bool big) {
    position.x = x;
    position.y = y;
    this->big = big;
}

std::shared_ptr<Entity> Orb::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this());
}

bool Orb::isBig() const {
    return big;
}

void Orb::Update(float dt) {
    view->Update(dt);
}