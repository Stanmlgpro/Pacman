//
// Created by stan on 10/15/25.
//

#include "Wall.h"
#include "Pacman.h"
#include "World.h"

namespace entities {
Wall::Wall(float x, float y) {
  position.x = x;
  position.y = y;
  setCollisionSize(2.0f);
}

std::shared_ptr<Entity> Wall::Interact(World &world) {
  return world.CollidesWithPacman(shared_from_this());
}

void Wall::Update(float dt) { view->Update(dt); }
} // namespace entities