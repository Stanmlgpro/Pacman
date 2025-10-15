//
// Created by stan on 10/15/25.
//

#include "Pacman.h"
#include "Ghost.h"
#include "Orb.h"

Pacman::Pacman(int x, int y) {
    position.x = x;
    position.y = y;
}

void Pacman::InteractWithWall() {
    moving = false;
}
std::shared_ptr<Entity> Pacman::InteractWithOrb(std::shared_ptr<Entity> orb) {
    return orb;
}
std::tuple<std::shared_ptr<Entity>, bool, bool> Pacman::InteractWithGhost(std::shared_ptr<Entity> ghost) {
    if (ghost->getFeared()) return std::make_tuple(ghost, false, false);
    lives--;
    if (lives == 0) return std::make_tuple(nullptr, false, true);
    return std::make_tuple(nullptr, true, false);
}

void Pacman::Update(float dt) {
    if (moving) Entity::Update(dt);
    moving = true;
}

int Pacman::getLives() const {
    return lives;
}
