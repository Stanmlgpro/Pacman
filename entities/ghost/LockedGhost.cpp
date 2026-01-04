//
// Created by stan1 on 09/11/2025.
//

#include "LockedGhost.h"
#include "entities/Pacman.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>

namespace entities {
LockedGhost::LockedGhost(const float x, const float y, std::shared_ptr<Pacman> pacman,
                         const std::vector<std::vector<bool>>& wallgrid, const int id, const float chasetime)
    : Ghost(x, y, std::move(pacman), wallgrid, id, chasetime) {
    // Create a ghost and set its speed
    setSpeed(8.5f);
}

float LockedGhost::distanceTurn(const std::vector<int> direction, const float dt) {
    if (dying)
        // If we are dying (eyes) Go back to startpos
        return BreathFirstDistance(direction, startpos, dt);
    if (feared)
        // Otherwise run from pacman (distance will be maximized when calling this instead of minimized)
        return BreathFirstDistance(direction, pacman->getPosition(), dt);
    // Otherwise return nothing since this ghost should not calculate otherwise and just choose a random direction
    return 0.f;
}

void LockedGhost::CalculateNextTurn(const float dt) {
    // Different algorithm for when we are feared or dying since we need to calculate in those cases
    if (dying || feared) {
        std::vector<int> direction;
        float best_distance = -1.f;
        std::vector<std::vector<int>> best_directions;

        for (const std::vector<int>& dir_try : IsAtIntersection()) {
            float dis = distanceTurn(dir_try, dt);
            // Maximize or minimize based on feared or dying
            if ((best_distance == -1.f) || (feared ? dis > best_distance : dis < best_distance)) {
                best_distance = dis;
                best_directions.clear();
                best_directions.push_back(dir_try);
            } else if (dis == best_distance) {
                best_directions.push_back(dir_try);
            }
        }
        // check for non-existent or singular best directions
        if (best_directions.empty())
            return;
        if (best_directions.size() == 1)
            this->direction = best_directions[0];
        // Otherwise we chose one at random
        else
            this->direction = best_directions[random.get(0, best_directions.size() - 1)];
        turnTimer = turnSpeed;

        return;
    }
    // If we are not feared or dying just choose a random direction out of the available
    auto possible_dir = IsAtIntersection();
    // check for empty possibles direction and wait a tick with a 50% chance
    if (possible_dir.empty())
        return;
    if (random.get(0, 1) == 0) {
        this->direction = {0, 0};
        return;
    }
    // Choose a random direction but discard backtracking
    if (possible_dir.size() != 1) {
        std::vector<int> opposite_dir = {-direction[0], -direction[1]};
        auto it = std::find(possible_dir.begin(), possible_dir.end(), opposite_dir);
        if (it != possible_dir.end() && possible_dir.size() > 1) {
            possible_dir.erase(it);
        }
    }
    int rand = random.get(0, possible_dir.size() - 1);
    direction = possible_dir[rand];
    // a little delay before checking if we are able to make turns again (prevents verry gittery behaviour at large
    // gaps)
    turnTimer = turnSpeed;
}
} // namespace entities