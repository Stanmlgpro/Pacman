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

void Ghost::CalculateNextTurn(float dt) {
    // Checks if we are at an intersection and then decides what route to take based on if it is feared or not
    // If we aren't one of the ghost that use it just take a random value by chance
    // direction[0] = -1|0|1
    // direction[1] = -1|0|1
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