//
// Created by stan on 10/15/25.
//

#include "Ghost.h"

Ghost::Ghost(int x, int y, std::shared_ptr<PacMan> pacman, std::vector<std::shared_ptr<Wall>> walls, int id) {
    position.x = x;
    position.y = y;
    this->pacman = pacman;
    this->walls = walls;
    this->id = id;
}

void Ghost::CalculateNextTurn(float dt) {
    // Checks if we are at an intersection and then decides what route to take based on if it is feared or not
    // If we aren't one of the ghost that use it just take a random value by chance
    // direction[0] = -1|0|1
    // direction[1] = -1|0|1
}

void Ghost::Update(float dt) {
    CalculateNextTurn(dt);
    Entity::Update(dt);
}

void Ghost::setFeared(bool feared) {
    this->feared = feared;
}
bool Ghost::getFeared() {
    return feared;
}