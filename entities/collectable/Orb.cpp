//
// Created by stan on 10/15/25.
//

#include "Orb.h"
#include "./entities/Pacman.h"
#include "World.h"
#include <iostream>

namespace entities {
Orb::Orb(float x, float y) {
    // Create an Orb with a position and collision
    position.x = x;
    position.y = y;
    setCollisionSize(0.85f);
}

std::shared_ptr<Entity> Orb::Interact(World& world) { return world.CollidesWithPacman(shared_from_this()); }
// Update the view
void Orb::Update(float dt) { view->Update(dt); }

// Make sure we cannot have won yet if any Orbs are still present
void Orb::checkWin(bool& check) { check = false; }
} // namespace entities