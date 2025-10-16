//
// Created by stan1 on 13/10/2025.
//

#include "Entity.h"

void Entity::Update(float dt) {
    if (direction.capacity() < 2) return;
    position.x += direction[0]*dt;
    position.y += direction[1]*dt;
}

Position Entity::getPosition() const {
    return position;
}

void Entity::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

std::vector<int> Entity::getDirection() const {
    return direction;
}

void Entity::setDirection(std::vector<int> direction) {
    this->direction = direction;
}