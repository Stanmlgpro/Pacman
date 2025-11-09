//
// Created by stan on 10/15/25.
//

#include "Ghost.h"
#include "entities/Pacman.h"
#include "World.h"
#include <iostream>

Ghost::Ghost(float x, float y, std::shared_ptr<Pacman> pacman, const std::vector<std::vector<bool>>& wallgrid, int id) {
    position.x = x;
    position.y = y;
    startpos = {x, y};
    this->pacman = pacman;
    this->wallgrid = wallgrid;
    this->id = id;
    direction = {0, 0};
    feared = false;
    mapwidth = static_cast<int>(wallgrid[0].size());
    mapheight = static_cast<int>(wallgrid.size());
}

std::shared_ptr<Entity> Ghost::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this());
}

void Ghost::Update(float dt) {
    if (feared) {
        fearcheck += dt;
        if (fearcheck >= feartime) {
            feared = false;
            fearcheck = 0.f;
        }
    }
    CalculateNextTurn(MoveDt(dt));
    Entity::Update(MoveDt(dt));
    view->Update(dt);
}

void Ghost::setFeared(bool feared) {
    this->feared = feared;
}
bool Ghost::getFeared() {
    return feared;
}
std::vector<float> Ghost::getStartPos() const {
    return startpos;
}
int Ghost::getId() const {
    return id;
}
float Ghost::MoveDt(float dt) const {
    auto sped = speed;
    if (direction[0] == 1 or direction[0] == -1) sped /= mapwidth;
    else sped /= mapheight;
    dt *= sped;
    return dt;
}