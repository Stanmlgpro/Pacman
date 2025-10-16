//
// Created by stan1 on 14/10/2025.
//

#include "World.h"
#include <fstream>
#include <iostream>
#include "Wall.h"
#include "Pacman.h"
#include <algorithm>
#include "Ghost.h"
#include "Orb.h"

World::World(std::string filename) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
    }
    int x = 0;
    int y = 0;
    int id;
    while (getline(file, line)) {
        wallGrid.push_back(std::vector<bool>());
        for (auto c : line) {
            if (c == '#') {
                entities.push_back(std::make_shared<Wall>(x, y));
                std::cout << "added wall at: " << x << ", " << y << std::endl;
                wallGrid[y].push_back(true);

            }
            if (c == '.') {
                entities.push_back(std::make_shared<Orb>(x, y, false));
                std::cout << "added little_orb at: " << x << ", " << y << std::endl;
                wallGrid[y].push_back(false);
            }
            if (c == 'o') {
                entities.push_back(std::make_shared<Orb>(x, y, true));
                std::cout << "added big_orb at: " << x << ", " << y << std::endl;
                wallGrid[y].push_back(false);
            }
            if (c == 'P') {
                pacman = std::make_shared<Pacman>(x, y);
                std::cout << "added pacman at: " << x << ", " << y << std::endl;
                wallGrid[y].push_back(false);
            }
            if (c == 'G') {
                entities.push_back(std::make_shared<Ghost>(x, y, pacman, wallGrid, id));
                std::cout << "added ghost at: " << x << ", " << y << std::endl;
                id++;
                wallGrid[y].push_back(false);
            }
            x++;
        }
        y++;
        x = 0;
    }
    file.close();
}

bool World::CollidesWithPacman(std::shared_ptr<Entity> entity, float dt) const {
    Position pacPos = pacman->getPosition();
    Position entPos = entity->getPosition();

    float dx = std::abs(pacPos.x + pacman->getDirection()[0]*dt - entPos.x);
    float dy = std::abs(pacPos.y + pacman->getDirection()[1]*dt - entPos.y);

    return (dx < 0.5f && dy < 0.5f);
}

void World::Update(float dt) {
    std::vector<std::shared_ptr<Entity>> removeables;
    bool fearing = false;
    for (auto e : entities) {
        if (CollidesWithPacman(e, dt)) {
            auto [to_remove, checker1, checker2] = e->Interact(*pacman);
            if (to_remove) removeables.push_back(to_remove);
            if (checker1 && checker2) fearing = true;
            if (checker1) {/* restart world*/}
            if (checker2) {/* game over*/}
        }
        e->Update(dt);
    }
    pacman->Update(dt);
    std::cout << pacman->getPosition().x << ", " << pacman->getPosition().y << std::endl;
    for (auto r : removeables) {
        entities.erase(std::remove(entities.begin(), entities.end(), r), entities.end());
    }
}
