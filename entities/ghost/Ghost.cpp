//
// Created by stan on 10/15/25.
//

#include "Ghost.h"
#include "entities/Pacman.h"
#include "World.h"
#include <iostream>

Ghost::Ghost(float x, float y, std::shared_ptr<Pacman> pacman, const std::vector<std::vector<bool>>& wallgrid, int id, float chasetime) {
    position.x = x;
    position.y = y;
    startpos = {x, y};
    this->pacman = pacman;
    this->wallgrid = wallgrid;
    this->id = id;
    direction = {0, 0};
    feared = false;
    mapwidth = static_cast<int>(wallgrid[0].size());
    mapheight = static_cast<int>(wallgrid.size());
    this->ChaseTime = chasetime;
    Chasing = false;
}

std::shared_ptr<Entity> Ghost::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this());
}

std::vector<std::vector<int>> Ghost::IsAtIntersection() const {
    auto gridPos = World::NormalizedToGrid(position.x, position.y, wallgrid);
    int gridX = static_cast<int>(gridPos[0]);
    int gridY = static_cast<int>(gridPos[1]);

    float tileSizeX = 2.0f / static_cast<float>(wallgrid[0].size());
    float tileSizeY = 2.0f / static_cast<float>(wallgrid.size());
    float cellCenterX = -1.0f + tileSizeX * (static_cast<float>(gridX) + 0.5f);
    float cellCenterY = -1.0f + tileSizeY * (static_cast<float>(gridY) + 0.5f);

    float distX = std::abs(position.x - cellCenterX);
    float distY = std::abs(position.y - cellCenterY);
    float epsilon = 0.003f;

    if (!(distX < epsilon && distY < epsilon))
        return {};

    std::vector<std::vector<int>> ret;
    std::vector<std::vector<int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int openPaths = 0;

    for (const auto& d : dirs) {
        int nx = gridX + d[0];
        int ny = gridY + d[1];

        if (ny < 0 || ny >= static_cast<int>(wallgrid.size()) ||
            nx < 0 || nx >= static_cast<int>(wallgrid[0].size()))
            continue;

        if (!wallgrid[ny][nx]) {
            openPaths++;
            ret.push_back(d);
        }
    }

    if (openPaths >= 3 || openPaths == 1)
        return ret;

    if (openPaths == 2) {
        bool left   = (gridX > 0) && !wallgrid[gridY][gridX - 1];
        bool right  = (gridX < static_cast<int>(wallgrid[0].size()) - 1) && !wallgrid[gridY][gridX + 1];
        bool up     = (gridY > 0) && !wallgrid[gridY - 1][gridX];
        bool down   = (gridY < static_cast<int>(wallgrid.size()) - 1) && !wallgrid[gridY + 1][gridX];

        bool hasHorizontal = left || right;
        bool hasVertical   = up || down;

        if (!(hasHorizontal && hasVertical))
            return {};
    }

    return ret;
}

void Ghost::Update(float dt) {
    if (feared) {
        fearcheck += dt;
        if (fearcheck >= feartime) {
            setFeared(false);
            fearcheck = 0.f;
        }
    }
    if (!Chasing) {
        ChaseTime -= dt;
        if (ChaseTime <= 0.f) {
            Chasing = true;
        }
        return;
    }
    if (turnTimer > 0.f)
        turnTimer -= dt;

    if (turnTimer <= 0.f)
        CalculateNextTurn(MoveDt(dt));
    Entity::Update(MoveDt(dt));
    view->Update(dt);
}

void Ghost::setFeared(bool feared) {
    this->feared = feared;
    if (feared) speed /= 2.f;
    else speed *= 2.f;
}
bool Ghost::getFeared() {
    return feared;
}
std::vector<float> Ghost::getStartPos() const {
    return startpos;
}
int Ghost::getId() const {
    return id;
}
float Ghost::MoveDt(float dt) const {
    auto sped = speed;
    if (direction[0] == 1 or direction[0] == -1) sped /= mapwidth;
    else sped /= mapheight;
    dt *= sped;
    return dt;
}