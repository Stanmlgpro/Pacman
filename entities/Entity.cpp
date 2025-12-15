//
// Created by stan1 on 13/10/2025.
//

#include "Entity.h"
#include <iostream>
#include <utility>

namespace entities {
Entity::Entity(int mapwidth, int mapheight) {
    this->mapwidth = mapwidth;
    this->mapheight = mapheight;
    position = {0.f, 0.f};
    direction = {0, 0};
}

float Entity::wrap(float v) {
    constexpr float min = -1.0f;
    constexpr float max = 1.0f;
    constexpr float range = max - min;

    v = std::fmod(v - min, range);
    if (v < 0.0f)
        v += range;
    return v + min;
}

void Entity::Update(float dt) {
    if (direction.size() < 2)
        return;
    position.x += direction[0] * dt;
    position.y += direction[1] * dt;

    position.x = wrap(position.x);
    position.y = wrap(position.y);
}

void Entity::Draw() const {
    if (view)
        view->Draw();
}

void Entity::setView(std::unique_ptr<views::View> view) { this->view = std::move(view); }

Position Entity::getPosition() const { return position; }

void Entity::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

std::vector<int> Entity::getDirection() const { return direction; }

void Entity::setDirection(std::vector<int> direction) { this->direction = std::move(direction); }

float Entity::getCollsionSize() const { return CollisionSize; }

void Entity::setCollisionSize(float size) { CollisionSize = size; }
} // namespace entities