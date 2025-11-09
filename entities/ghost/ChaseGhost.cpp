//
// Created by stan1 on 09/11/2025.
//

#include "ChaseGhost.h"
#include <algorithm>
#include "World.h"
#include "entities/Pacman.h"
#include <iostream>

ChaseGhost::ChaseGhost(float x, float y, std::shared_ptr<Pacman> pacman, const std::vector<std::vector<bool>>& wallgrid, int id) : Ghost(x, y, pacman, wallgrid, id) {
    speed = 11.f;
}

float ChaseGhost::tryTurn(std::vector<int> direction, float dt) {
    auto buffer = direction;
    if (buffer[0] == 0 && buffer[1] == 0) return -1;

    Position pos = position;
    auto gridPos = World::NormalizedToGrid(position.x, position.y, wallgrid);
    int currentGridX = static_cast<int>(gridPos[0]);
    int currentGridY = static_cast<int>(gridPos[1]);

    int targetGridX = currentGridX + buffer[0];
    int targetGridY = currentGridY + buffer[1];

    bool canMove = true;
    if (targetGridX < 0 or targetGridX >= static_cast<int>(wallgrid[0].size()) or targetGridY < 0 or targetGridY >= static_cast<int>(wallgrid.size())) canMove = false;
    else if (wallgrid[targetGridY][targetGridX]) canMove = false;

    if (!canMove) return -1;

    float tileSizeX = 2.0f / static_cast<float>(wallgrid[0].size());
    float tileSizeY = 2.0f / static_cast<float>(wallgrid.size());

    float cellCenterX = -1.0f + tileSizeX * (static_cast<float>(currentGridX) + 0.5f);
    float cellCenterY = -1.0f + tileSizeY * (static_cast<float>(currentGridY) + 0.5f);

    float distX = std::abs(position.x - cellCenterX);
    float distY = std::abs(position.y - cellCenterY);

    float epsilon = 0.001f;

    if (!(distX < epsilon && distY < epsilon)) return -1;

    return distanceTurn(direction, dt);
}

float ChaseGhost::distanceTurn(std::vector<int> direction, float dt) {
    float newX = position.x + direction[0] * speed * dt;
    float newY = position.y + direction[1] * speed * dt;
    float dis = std::abs(newX - pacman->getPosition().x) + std::abs(newY - pacman->getPosition().y);
    return dis;
}

void ChaseGhost::CalculateNextTurn(float dt) {
    std::vector<int> direction;
    float best_distance = -1.f;
    std::vector<std::vector<int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    for (std::vector<int> dir_try : directions) {
        float dis = tryTurn(dir_try, dt);
        if (dis == -1.f) continue;
        if (dis >= 0 && (best_distance == -1.f || feared ? dis > best_distance : dis < best_distance)) {
            best_distance = dis;
            direction = dir_try;
        }
    }
    if (direction.empty()) return;
    this->direction = direction;
}
