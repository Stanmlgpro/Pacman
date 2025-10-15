//
// Created by stan on 10/15/25.
//

#include "Wall.h"

Wall::Wall(int x, int y) {
    position.x = x;
    position.y = y;
}

void Wall::Update(float dt) {}

void Wall::Interact(std::shared_ptr<Entity> other) {

}

Wall::~Wall() = default;
