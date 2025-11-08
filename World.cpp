//
// Created by stan1 on 14/10/2025.
//

#include "World.h"
#include <fstream>
#include <iostream>
#include "entities/Wall.h"
#include "entities/Pacman.h"
#include <algorithm>
#include "entities/ghost/Ghost.h"
#include "entities/Orb.h"
#include "factory/EntityFactory.h"
#include "singleton/Stopwatch.h"

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

    float tileSizeX = 2.0f / static_cast<float>(width);
    float tileSizeY = 2.0f / static_cast<float>(height);

    int y = 0;
    std::string line2;
    while (getline(file, line2)) {
        wallGrid.emplace_back();
        for (int x = 0; x < static_cast<int>(line2.size()); x++) {
            char c = line2[x];

            float normX = -1.0f + tileSizeX * (static_cast<float>(x) + 0.5f);
            float normY = -1.0f + tileSizeY * (static_cast<float>(y) + 0.5f);

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

std::vector<int> World::NormalizedToGrid(float normX, float normY) const {

    int gridWidth = static_cast<int>(wallGrid[0].size());
    int gridHeight = static_cast<int>(wallGrid.size());

    float tileSizeX = 2.0f / static_cast<float>(gridWidth);
    float tileSizeY = 2.0f / static_cast<float>(gridHeight);

    int gridX = static_cast<int>((normX + 1.0f) / tileSizeX);
    int gridY = static_cast<int>((normY + 1.0f) / tileSizeY);

    return {gridX, gridY};
}

std::shared_ptr<Entity> World::CollidesWithPacman(std::shared_ptr<Wall> wall) {
    Position pacPos = pacman->getPosition();
    Position wallPos = wall->getPosition();

    float epsilon = 0.005f;
    float dx = std::abs(pacPos.x + pacman->getDirection()[0]*dt - wallPos.x) + epsilon;
    float dy = std::abs(pacPos.y + pacman->getDirection()[1]*dt - wallPos.y) + epsilon;

    if (dx < 2.f/wallGrid[0].size() && dy < 2.f/wallGrid.size()) pacman->setMoving(false);
    return nullptr;
}

std::shared_ptr<Entity> World::CollidesWithPacman(std::shared_ptr<Orb> orb) {
    Position pacPos = pacman->getPosition();
    Position orbPos = orb->getPosition();

    float dx = std::abs(pacPos.x + pacman->getDirection()[0]*dt - orbPos.x);
    float dy = std::abs(pacPos.y + pacman->getDirection()[1]*dt - orbPos.y);

    float size = orb->isBig() ? 1.25f : 0.85f;
    float collisionDistX = size / wallGrid[0].size();
    float collisionDistY = size / wallGrid.size();

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

void World::TryBuffer() {
    auto buffer = pacman->getDirectionBuffer();
    if (buffer[0] == 0 && buffer[1] == 0) return;

    Position pacPos = pacman->getPosition();
    auto gridPos = NormalizedToGrid(pacPos.x, pacPos.y);
    int currentGridX = static_cast<int>(gridPos[0]);
    int currentGridY = static_cast<int>(gridPos[1]);

    int targetGridX = currentGridX + buffer[0];
    int targetGridY = currentGridY + buffer[1];

    bool canMove = true;
    if (targetGridX < 0 or targetGridX >= static_cast<int>(wallGrid[0].size()) or targetGridY < 0 or targetGridY >= static_cast<int>(wallGrid.size())) canMove = false;
    else if (wallGrid[targetGridY][targetGridX]) canMove = false;

    if (!canMove) return;

    float tileSizeX = 2.0f / static_cast<float>(wallGrid[0].size());
    float tileSizeY = 2.0f / static_cast<float>(wallGrid.size());

    float cellCenterX = -1.0f + tileSizeX * (static_cast<float>(currentGridX) + 0.5f);
    float cellCenterY = -1.0f + tileSizeY * (static_cast<float>(currentGridY) + 0.5f);

    float distX = std::abs(pacPos.x - cellCenterX);
    float distY = std::abs(pacPos.y - cellCenterY);

    float epsilon = 0.005f;

    if (distX < epsilon && distY < epsilon) pacman->setDirection(buffer);
}

void World::Update() {
    Stopwatch& stopwatch = Stopwatch::getInstance();
    stopwatch.tick();
    dt = stopwatch.getDeltaTime();
    if (dt > 0.06f) dt = 0.06f;
    TryBuffer();
    std::vector<std::shared_ptr<Entity>> removeables;
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
    } if (movement == DOWN) {
        pacman->Down();
    } if (movement == LEFT) {
        pacman->Left();
    } if (movement == RIGHT) {
        pacman->Right();
    }
}
