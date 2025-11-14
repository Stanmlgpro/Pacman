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
#include "Score.h"

World::World(std::string filename, std::shared_ptr<EntityFactory> entity_factory, std::shared_ptr<WorldSound> world_sounds, std::string player) {
    this->filename = filename;
    this->entity_factory = entity_factory;
    this->score = std::make_unique<Score>(player);
    this->world_sounds = world_sounds;

    dt = 0;
    difficulty = 0;
    fear_time = 7;
    ghost_speed_mul = 0.4;
    loadMap_reset();
}

void World::loadMap_reset() {
    fear_time = fear_time * 0.9;
    ghost_speed_mul = ghost_speed_mul * 1.3;
    entities.clear();
    wallGrid.clear();
    std::ifstream file(filename);
    std::string line;
    int width = 0, height = 0;

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

    struct GhostSpawn {
        float x, y;
        int id;
    };
    std::vector<GhostSpawn> ghostSpawns;

    int y = 0;
    std::string line2;
    int id = 0;

    while (getline(file, line2)) {
        wallGrid.emplace_back();
        for (int x = 0; x < static_cast<int>(line2.size()); x++) {
            char c = line2[x];
            float normX = -1.0f + tileSizeX * (x + 0.5f);
            float normY = -1.0f + tileSizeY * (y + 0.5f);

            if (c == '#') {
                entities.push_back(entity_factory->createWall(normX, normY));
            } else if (c == '.') {
                entities.push_back(entity_factory->createOrb(normX, normY));
            } else if (c == 'o') {
                entities.push_back(entity_factory->createBigOrb(normX, normY));
            } else if (c == 'P') {
                pacman = entity_factory->createPacman(7.5f, width, height, normX, normY);
            } else if (c == 'G') {
                ghostSpawns.push_back({normX, normY, id++});
            }

            wallGrid[y].push_back(c == '#');
        }
        y++;
    }
    file.close();

    for (auto& g : ghostSpawns) {
        auto ghost = entity_factory->createGhost(g.x, g.y, pacman, wallGrid, g.id, true);
        ghost->setFearTime(fear_time);
        ghost->setSpeed(ghost->getSpeed() * ghost_speed_mul);
        entities.push_back(ghost);
    }
}

std::vector<int> World::NormalizedToGrid(float normX, float normY, std::vector<std::vector<bool>> wallGrid) {

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
        if (orb->isBig()) {
            fearmode = true;
            world_sounds->FruitEaten();
        }
        else world_sounds->OrbEaten();

        score->orbEaten(orb->isBig());
        return orb;
    }
    return nullptr;
}

std::shared_ptr<Entity> World::CollidesWithPacman(std::shared_ptr<Ghost> ghost) {
    if (ghost->getDying()) return nullptr;
    Position pacPos = pacman->getPosition();
    Position ghostPos = ghost->getPosition();

    float epsilon = 0.005f;
    float dx = std::abs(pacPos.x + pacman->getDirection()[0]*dt - ghostPos.x) + epsilon;
    float dy = std::abs(pacPos.y + pacman->getDirection()[1]*dt - ghostPos.y) + epsilon;

    if (dx < 1.5f/wallGrid[0].size() && dy < 1.5f/wallGrid.size()) {
        if (ghost->getFeared()) {
            ghost->setDying(true);
            score->ghostEaten();
            world_sounds->GhostEaten();
            return nullptr;
        }
        pacman->setLives(pacman->getLives() - 1);
        world_sounds->PacmanDying();
        if (pacman->getLives() <= 0) {
            return pacman;
        }
        for (auto e : entities) {
            e->reset();
        }
        pacman->setDying(true);
    }
    return nullptr;
}

void World::TryBuffer() {
    auto buffer = pacman->getDirectionBuffer();
    if (buffer[0] == 0 && buffer[1] == 0) return;

    Position pacPos = pacman->getPosition();
    auto gridPos = NormalizedToGrid(pacPos.x, pacPos.y, wallGrid);
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

bool World::Update() {
    Stopwatch& stopwatch = Stopwatch::getInstance();
    stopwatch.tick();
    dt = stopwatch.getDeltaTime();
    if (dt > 0.06f) dt = 0.06f;
    if (pacman->isDead()) pacman->reset();
    bool new_level = true;
    TryBuffer();
    std::vector<std::shared_ptr<Entity>> removeables;
    for (auto e : entities) {
        e->checkWin(new_level);
        if (fearmode) {
            e->setFeared(fearmode);
            world_sounds->FearMode();
        }
        removeables.push_back(e->Interact(*this));
        if (!pacman->getDying()) {
            e->Update(dt);
        }
    }
    pacman->Update(dt);
    if (new_level) {
        int lives = pacman->getLives();
        difficulty++;
        loadMap_reset();
        pacman->setLives(lives);
        world_sounds->Start();
        return false;
    }
    for (auto& r : removeables) {
        if (r) {
            if (r == pacman) return true;
            entities.erase(std::remove(entities.begin(), entities.end(), r), entities.end());
        }
    }
    for (auto& e : to_add) {
        entities.push_back(e);
    }
    to_add.clear();
    if (fearmode) fear_timer += dt;
    else if (fear_timer != 0) {
        fear_timer += dt;
        if (fear_timer > fear_time) {
            fear_timer = 0;
            world_sounds->EndFearMode();
        }
    }
    if (fear_timer == 0) world_sounds->EndFearMode();
    std::cout << fear_timer << " " << fear_time << std::endl;
    fearmode = false;
    return false;
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

std::shared_ptr<Entity> World::CollidesWithPacman(std::shared_ptr<Pacman> pacman) { return nullptr; }