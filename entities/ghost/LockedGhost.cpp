//
// Created by stan1 on 09/11/2025.
//

#include "LockedGhost.h"
#include <cmath>
#include "entities/Pacman.h"
#include <iostream>
#include <algorithm>

LockedGhost::LockedGhost(float x, float y, std::shared_ptr<Pacman> pacman, const std::vector<std::vector<bool>>& wallgrid, int id, float chasetime) : Ghost(x, y, pacman, wallgrid, id, chasetime) {
    speed = 8.5f;
}

float LockedGhost::distanceTurn(std::vector<int> direction, float dt) {
    if (feared) {
        float newX = position.x + direction[0] * speed * dt;
        float newY = position.y + direction[1] * speed * dt;
        float dis = std::abs(newX - pacman->getPosition().x) + std::abs(newY - pacman->getPosition().y);
        return dis;
    }
    return 0.f;
}

void LockedGhost::CalculateNextTurn(float dt) {
    auto possible_dir = IsAtIntersection();
    if (possible_dir.empty()) return;
    if (random.get(0, 1) == 0) {
        this->direction = {0, 0};
        return;
    }
    if (possible_dir.size() != 1) {
        std::vector<int> opposite_dir = {-direction[0], -direction[1]};
        auto it = std::find(possible_dir.begin(), possible_dir.end(), opposite_dir);
        if (it != possible_dir.end() && possible_dir.size() > 1) {
            possible_dir.erase(it);
        }
    }
    std::vector<int> opposite_dir = {-direction[0], -direction[1]};
    for (auto it = possible_dir.begin(); it != possible_dir.end(); ++it) {
        if ((*it)[0] == opposite_dir[0] && (*it)[1] == opposite_dir[1]) {
            if (possible_dir.size() > 1) {
                possible_dir.erase(it);
            }
            break;
        }
    }
    int rand = random.get(0, possible_dir.size() - 1);
    direction = possible_dir[rand];
    turnTimer = turnSpeed;
}