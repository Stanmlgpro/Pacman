//
// Created by stan1 on 09/11/2025.
//

#include "LockedGhost.h"
#include "entities/Pacman.h"
#include <algorithm>
#include <cmath>
#include <iostream>

namespace entities {
LockedGhost::LockedGhost(float x, float y, std::shared_ptr<Pacman> pacman,
                         const std::vector<std::vector<bool>>& wallgrid, int id, float chasetime)
    : Ghost(x, y, pacman, wallgrid, id, chasetime) {
    setSpeed(8.5f);
}

float LockedGhost::distanceTurn(std::vector<int> direction, float dt) {
    if (dying)
        return BreathFirstDistance(direction, startpos, dt);
    if (feared)
        return BreathFirstDistance(direction, pacman->getPosition(), dt);
    return 0.f;
}

void LockedGhost::CalculateNextTurn(float dt) {
    if (dying || feared) {
        std::vector<int> direction;
        float best_distance = -1.f;
        std::vector<std::vector<int>> best_directions;

        for (const std::vector<int>& dir_try : IsAtIntersection()) {
            float dis = distanceTurn(dir_try, dt);
            if ((best_distance == -1.f) || (feared ? dis > best_distance : dis < best_distance)) {
                best_distance = dis;
                best_directions.clear();
                best_directions.push_back(dir_try);
            } else if (dis == best_distance) {
                best_directions.push_back(dir_try);
            }
        }
        if (best_directions.empty())
            return;
        if (best_directions.size() == 1)
            this->direction = best_directions[0];
        else
            this->direction = best_directions[random.get(0, best_directions.size() - 1)];
        turnTimer = turnSpeed;

        return;
    }
    auto possible_dir = IsAtIntersection();
    if (possible_dir.empty())
        return;
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
    int rand = random.get(0, possible_dir.size() - 1);
    direction = possible_dir[rand];
    turnTimer = turnSpeed;
}
} // namespace entities