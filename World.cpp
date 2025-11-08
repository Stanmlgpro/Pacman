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

    dt = 0;
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

            if (c == '#') {
                entities.push_back(entity_factory->createWall(normX, normY));
            }
            else if (c == '.') {
                entities.push_back(entity_factory->createOrb(normX, normY));
            }
            else if (c == 'o') {
                entities.push_back(entity_factory->createBigOrb(normX, normY));
            }
            else if (c == 'P') {
                pacman = entity_factory->createPacman(10.f, width, height, normX, normY);
            }
            else if (c == 'G') {
                entities.push_back(entity_factory->createGhost(normX, normY, pacman, wallGrid, id++));
            }
            wallGrid[y].push_back(c == '#');
        }
        y++;
    }
    file.close();
}

std::shared_ptr<Entity> World::CollidesWithPacman(std::shared_ptr<Wall> wall) {
    Position pacPos = pacman->getPosition();
    Position wallPos = wall->getPosition();

    float dx = std::abs(pacPos.x + pacman->getDirection()[0]*dt - wallPos.x);
    float dy = std::abs(pacPos.y + pacman->getDirection()[1]*dt - wallPos.y);

    if (dx < 2.f/wallGrid[0].size() && dy < 2.f/wallGrid.size()) pacman->setMoving(false);
    return nullptr;
}

std::shared_ptr<Entity> World::CollidesWithPacman(std::shared_ptr<Orb> orb) {
    Position pacPos = pacman->getPosition();
    Position orbPos = orb->getPosition();

    float dx = std::abs(pacPos.x + pacman->getDirection()[0]*dt - orbPos.x);
    float dy = std::abs(pacPos.y + pacman->getDirection()[1]*dt - orbPos.y);

    // Adjust collision threshold based on orb size
    float threshold = orb->isBig() ? 1.25f : 0.85f;
    float collisionDistX = threshold / wallGrid[0].size();
    float collisionDistY = threshold / wallGrid.size();

    if (dx < collisionDistX && dy < collisionDistY) {
        if (orb->isBig()) fearmode = true;
        return orb;
    }
    return nullptr;
}

std::shared_ptr<Entity> World::CollidesWithPacman(std::shared_ptr<Ghost> ghost) {
    return nullptr;
}

std::shared_ptr<Entity> World::CollidesWithPacman(std::shared_ptr<Pacman> pacman) {
    return nullptr;
}

void World::Update() {
    Stopwatch& stopwatch = Stopwatch::getInstance();
    stopwatch.tick();
    dt = stopwatch.getDeltaTime();
    if (dt > 0.06f) dt = 0.06f;

    std::vector<std::shared_ptr<Entity>> removeables;
    bool fearing = false;
    for (auto e : entities) {
        removeables.push_back(e->Interact(*this));
        e->Update(dt);
    }
    pacman->Update(dt);
    for (auto r : removeables) {
        if (r) entities.erase(std::remove(entities.begin(), entities.end(), r), entities.end());
    }
}

std::vector<std::shared_ptr<Entity>> World::getEntities() {
    return entities;
}

void World::Render() {
    for (auto entity : entities) {
        entity->Draw();
    }
    pacman->Draw();
}

void World::movePacman(MOVE movement) {
    if (movement == UP) {
        pacman->Up();
    }
    if (movement == DOWN) {
        pacman->Down();
    }if (movement == LEFT) {
        pacman->Left();
    }
    if (movement == RIGHT) {
        pacman->Right();
    }

}
