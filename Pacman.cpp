//
// Created by stan on 10/15/25.
//

#include "Pacman.h"
#include <iostream>

#include "Ghost.h"
#include "Orb.h"
#include "Wall.h"
#include "World.h"

Pacman::Pacman(float speed, int mapwidth, int mapheight, float x, float y) : Entity(mapwidth, mapheight) {
    position.x = x;
    position.y = y;
    direction.reserve(2);
    direction.push_back(1);
    direction.push_back(0);
    direction_buffer.reserve(2);
    direction_buffer.push_back(0);
    direction_buffer.push_back(0);
    this->speed = speed;
}

std::shared_ptr<Entity> Pacman::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this());
} //function that will never be called

void Pacman::Update(float dt) {
    if (moving) Entity::Update(MoveDt(dt));
    moving = true;
}

int Pacman::getLives() const {
    return lives;
}
void Pacman::setLives(int lives) {
    this->lives = lives;
}

void Pacman::setMoving(bool moving) {
    this->moving = moving;
}
void Pacman::Up() {
    direction_buffer[0] = 0;
    direction_buffer[1] = -1;
}
void Pacman::Down() {
    direction_buffer[0] = 0;
    direction_buffer[1] = 1;
}
void Pacman::Left() {
    direction_buffer[0] = -1;
    direction_buffer[1] = 0;
}
void Pacman::Right() {
    direction_buffer[0] = 1;
    direction_buffer[1] = 0;
}
void Pacman::setDirectionBuffer(std::vector<int> buffer) {
    direction_buffer = buffer;
}
std::vector<int> Pacman::getDirectionBuffer() const {
    return direction_buffer;
}
float Pacman::MoveDt(float dt) const {
    auto sped = speed;
    if (direction[0] == 1 or direction[0] == -1) sped /= mapwidth;
    else sped /= mapheight;
    dt *= sped;
    return dt;
}