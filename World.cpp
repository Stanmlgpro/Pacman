//
// Created by stan1 on 14/10/2025.
//

#include "World.h"
#include <fstream>
#include <iostream>
#include "Wall.h"
#include "Pacman.h"
#include <algorithm>

World::World(std::string filename) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
    }
    int x = 0;
    int y = 0;
    while (getline(file, line)) {
        for (auto c : line) {
            x++;
            if (c == '#') {
                walls.push_back(std::make_shared<Wall>(x, y));
                std::cout << "added wall at: " << x << ", " << y << std::endl;
            }
        }
        y++;
        x = 0;
    }
    file.close();
}

bool World::CollidesWithPacman(std::shared_ptr<Entity> entity) const {
    Position pacPos = pacman->getPosition();
    Position entPos = entity->getPosition();

    float dx = std::abs(pacPos.x - entPos.x);
    float dy = std::abs(pacPos.y - entPos.y);

    return (dx < 0.5f && dy < 0.5f);
}

void World::Update(float dt) {

    bool fearing = false;
    for (auto wall : walls) {
        if (CollidesWithPacman(wall)) pacman->InteractWithWall();
    }
    for (auto orb : orbs) {
        if (CollidesWithPacman(orb)) {
            auto to_remove = pacman->InteractWithOrb(orb);
            fearing = orb->isBig();
            if (to_remove) orbs.erase(std::remove(orbs.begin(), orbs.end(), to_remove), orbs.end());
        }
    }
    for (auto ghost : ghosts) {
        if (fearing) ghost->setFeared(true);
        if (CollidesWithPacman(ghost)) {
            auto result = pacman->InteractWithGhost(ghost);
        }
    }
    pacman->Update(dt);
    for (auto ghost : ghosts) {
        ghost->Update(dt);
    }
}
