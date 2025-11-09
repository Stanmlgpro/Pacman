//
// Created by stan on 10/15/25.
//

#include "Ghost.h"
#include "entities/Pacman.h"
#include "World.h"

Ghost::Ghost(float x, float y, std::shared_ptr<Pacman> pacman, const std::vector<std::vector<bool>>& wallgrid, int id) {
    position.x = x;
    position.y = y;
    this->pacman = pacman;
    this->wallgrid = wallgrid;
    this->id = id;
    direction = {0, 0};
    feared = false;
}

std::shared_ptr<Entity> Ghost::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this());
}

void Ghost::Update(float dt) {
    CalculateNextTurn(dt);
    Entity::Update(dt);
    view->Update(dt);
}

void Ghost::setFeared(bool feared) {
    this->feared = feared;
}
bool Ghost::getFeared() {
    return feared;
}