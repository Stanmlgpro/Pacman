//
// Created by stan on 10/15/25.
//

#include "Wall.h"
#include "Pacman.h"
#include "World.h"

namespace entities {
Wall::Wall(const float x, const float y) {
    // Create a Wall with a position and collision
    position.x = x;
    position.y = y;
    setCollisionSize(2.0f);
}

std::shared_ptr<Entity> Wall::Interact(World& world) { return world.CollidesWithPacman(shared_from_this()); }
// Update the view
void Wall::Update(const float dt) { view->Update(dt); }
} // namespace entities