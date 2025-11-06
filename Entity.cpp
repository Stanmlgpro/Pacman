//
// Created by stan1 on 13/10/2025.
//

#include "Entity.h"
#include <iostream>

void Entity::Update(float dt) {
    if (direction.capacity() < 2) return;
    position.x += direction[0]*dt;
    position.y += direction[1]*dt;
}

void Entity::Draw() {
    if (view) {
        view->Draw();
        std::cout << "tried to draw an entity" << std::endl;
    }
}

void Entity::setView(std::unique_ptr<View> view) {
    this->view = std::move(view);
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