//
// Created by stan1 on 09/11/2025.
//

#include "ChaseGhost.h"
#include <algorithm>
#include "World.h"
#include "entities/Pacman.h"
#include <iostream>

ChaseGhost::ChaseGhost(float x, float y, std::shared_ptr<Pacman> pacman, const std::vector<std::vector<bool>>& wallgrid, int id) : Ghost(x, y, pacman, wallgrid, id) {
    speed = 9.f;
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

    for (std::vector<int> dir_try : IsAtIntersection()) {
        float dis = distanceTurn(dir_try, dt);
        if (dis >= 0 && (best_distance == -1.f || (feared ? dis > best_distance : dis < best_distance))) {
            best_distance = dis;
            direction = dir_try;
        }
    }
    if (direction.empty()) return;

    this->direction = direction;
}
