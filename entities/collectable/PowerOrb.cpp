//
// Created by stan1 on 11/12/2025.
//

#include "PowerOrb.h"
#include "World.h"
#include <iostream>

namespace entities {
PowerOrb::PowerOrb(float x, float y) {
    // Create a PowerOrb with a position and collision
    position.x = x;
    position.y = y;
    setCollisionSize(1.25f);
}

std::shared_ptr<Entity> PowerOrb::Interact(World& world) { return world.CollidesWithPacman(shared_from_this()); }

    // Update the view
void PowerOrb::Update(float dt) { view->Update(dt); }

    // Make sure we cannot have won yet if any PowerOrbs are still present
void PowerOrb::checkWin(bool& check) { check = false; }
} // namespace entities
