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
                entities.push_back(std::make_shared<Wall>(x, y));
                std::cout << "added wall at: " << x << ", " << y << std::endl;
            }
        }
        y++;
        x = 0;
    }
    file.close();
    entities.push_back(std::make_shared<Pacman>(x, y));
}

bool World::CollidesWithPacman(std::shared_ptr<Entity> entity, float dt) const {
    Position pacPos = pacman->getPosition();
    Position entPos = entity->getPosition();

    float dx = std::abs(pacPos.x + pacman->getDirection()[0]*dt - entPos.x);
    float dy = std::abs(pacPos.y + pacman->getDirection()[1]*dt - entPos.y);

    return (dx < 0.5f && dy < 0.5f);
}

void World::Update(float dt) const {
    bool fearing = false;
    for (auto e : entities) {
        if (CollidesWithPacman(e, dt)) {
            auto [to_remove, checker1, checker2] = e->Interact(*pacman);
            std::cout << "pacman is colliding" << std::endl;
        }
        e->Update(dt);
    }
    pacman->Update(dt);
}
