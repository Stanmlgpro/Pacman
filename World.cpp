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
#include "EntityFactory.h"
#include "Stopwatch.h"

World::World(std::string filename, std::shared_ptr<EntityFactory> entity_factory) {
    this->entity_factory = entity_factory;

    std::ifstream file(filename);
    std::string line;
    int width = 0;
    int height = 0;
    int id = 0;

    while (getline(file, line)) {
        width = std::max(width, static_cast<int>(line.size()));
        height++;
    }
    file.close();

    entity_factory->getCamera()->setMapSize(width, height);
    file.open(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }

    int y = 0;
    std::string line2;
    while (getline(file, line2)) {
        wallGrid.emplace_back();
        for (int x = 0; x < static_cast<int>(line2.size()); x++) {
            char c = line2[x];
            float normX = (static_cast<float>(x) / (width - 1)) * 2.f - 1.f;
            float normY = (static_cast<float>(y) / (height - 1)) * 2.f - 1.f;

            if (c == '#')
                entities.push_back(entity_factory->createWall(normX, normY));
            else if (c == '.')
                entities.push_back(entity_factory->createOrb(normX, normY));
            else if (c == 'o')
                entities.push_back(entity_factory->createBigOrb(normX, normY));
            else if (c == 'P')
                pacman = entity_factory->createPacman(normX, normY);
            else if (c == 'G')
                entities.push_back(entity_factory->createGhost(normX, normY, pacman, wallGrid, id++));

            wallGrid[y].push_back(c == '#');
        }
        y++;
    }
    file.close();
}

bool World::CollidesWithPacman(std::shared_ptr<Entity> entity, float dt) const {
    Position pacPos = pacman->getPosition();
    Position entPos = entity->getPosition();

    float dx = std::abs(pacPos.x + pacman->getDirection()[0]*dt - entPos.x);
    float dy = std::abs(pacPos.y + pacman->getDirection()[1]*dt - entPos.y);

    return (dx < 1.f && dy < 1.f);
}

void World::Update() {
    Stopwatch& stopwatch = Stopwatch::getInstance();
    stopwatch.tick();
    float dt = stopwatch.getDeltaTime();

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
    for (auto r : removeables) {
        entities.erase(std::remove(entities.begin(), entities.end(), r), entities.end());
    }
}

std::vector<std::shared_ptr<Entity>> World::getEntities() {
    return entities;
}

void World::Render() {
    for (auto entity : entities) {
        entity->Draw();
    }
}
