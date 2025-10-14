//
// Created by stan1 on 14/10/2025.
//

#include "World.h"

World::World(std::string filename) {
}

void World::Update(float dt) {
    pacman->Update(dt);
    for (auto ghost : ghosts) {
        ghost->Update(dt);
    }
    for (auto non_movable : non_movables) {
        non_movable->Update(dt);
    }
}
