//
// Created by stan1 on 13/10/2025.
//

#include "Entity.h"
#include <iostream>
#include <utility>

namespace entities {
Entity::Entity(const int mapwidth, const int mapheight) {
    // set all variables
    this->mapwidth = mapwidth;
    this->mapheight = mapheight;
    position = {0.f, 0.f};
    direction = {0, 0};
}

float Entity::wrap(float v) {
    // get the range via the maximum and minimum floats
    constexpr float min = -1.0f;
    constexpr float max = 1.0f;
    constexpr float range = max - min;

    // used modulo to wrap the float
    v = std::fmod(v - min, range);
    // and return it after making sure it is between the range again
    if (v < 0.0f)
        v += range;
    return v + min;
}

void Entity::Update(float dt) {
    // check for incorrect directions
    if (direction.size() < 2)
        return;
    // update the position
    position.x += direction[0] * dt;
    position.y += direction[1] * dt;
    // and wrap the position
    position.x = wrap(position.x);
    position.y = wrap(position.y);
}

void Entity::Draw() const {
    // draw the view if present
    if (view)
        view->Draw();
}
// simple setters and getters
void Entity::setView(std::unique_ptr<views::View> view) { this->view = std::move(view); }

Position Entity::getPosition() const { return position; }

void Entity::setPosition(const float x, const float y) {
    position.x = x;
    position.y = y;
}

std::vector<int> Entity::getDirection() const { return direction; }

void Entity::setDirection(std::vector<int> direction) { this->direction = std::move(direction); }

float Entity::getCollsionSize() const { return CollisionSize; }

void Entity::setCollisionSize(const float size) { CollisionSize = size; }
} // namespace entities