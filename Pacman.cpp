//
// Created by stan on 10/15/25.
//

#include "Pacman.h"
#include <iostream>

#include "Ghost.h"
#include "Orb.h"
#include "Wall.h"

Pacman::Pacman(int x, int y) {
    position.x = x;
    position.y = y;
    direction.reserve(2);
    direction.push_back(-1);
    direction.push_back(0);
    direction_buffer.reserve(2);
    direction_buffer.push_back(0);
    direction_buffer.push_back(0);
}

std::tuple<std::shared_ptr<Entity>, bool, bool> Pacman::Interact(Pacman& pacman) {
    std::cout << "collided with pacman" << std::endl;
    return std::make_tuple(nullptr, false, false);
} //function that will never be called
std::tuple<std::shared_ptr<Entity>, bool, bool>  Pacman::InteractWith(std::shared_ptr<Wall> wall) {
    std::cout << "collided with wall" << std::endl;
    moving = false;
    return std::make_tuple(nullptr, false, false);
}
std::tuple<std::shared_ptr<Entity>, bool, bool>  Pacman::InteractWith(std::shared_ptr<Orb> orb) {
    std::cout << "collided with orb" << std::endl;
    return std::make_tuple(orb, true, true);
}
std::tuple<std::shared_ptr<Entity>, bool, bool> Pacman::InteractWith(std::shared_ptr<Ghost> ghost) {
    std::cout << "collided with ghost" << std::endl;
    if (ghost->getFeared()) return std::make_tuple(ghost, false, false);
    lives--;
    if (lives == 0) return std::make_tuple(nullptr, false, true);
    return std::make_tuple(nullptr, true, false);
}

void Pacman::setDirection(std::vector<int> direction) {
    direction_buffer = direction;
}

void Pacman::Update(float dt) {
    if (moving) {
        Entity::Update(dt);
    }
    moving = true;
}

int Pacman::getLives() const {
    return lives;
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