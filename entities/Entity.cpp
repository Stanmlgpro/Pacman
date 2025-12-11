//
// Created by stan1 on 13/10/2025.
//

#include "Entity.h"
#include <iostream>

namespace entities {
    Entity::Entity(int mapwidth, int mapheight) {
        this->mapwidth = mapwidth;
        this->mapheight = mapheight;
        position = {0.f, 0.f};
        direction = {0, 0};
    }

    void Entity::Update(float dt) {
        if (direction.size() < 2) return;
        position.x += direction[0]*dt;
        position.y += direction[1]*dt;

    }

    void Entity::Draw() const {
        if (view) view->Draw();
    }

    void Entity::setView(std::unique_ptr<views::View> view) {
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
}