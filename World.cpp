//
// Created by stan1 on 14/10/2025.
//

#include "World.h"
#include <fstream>
#include <iostream>
#include "Wall.h"

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

void World::Update(float dt) {

    pacman->Update(dt);
    for (auto ghost : ghosts) {
        ghost->Update(dt);
    }
}
