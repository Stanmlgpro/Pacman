//
// Created by stan1 on 09/11/2025.
//

#include "ChaseGhost.h"
#include "World.h"
#include "entities/Pacman.h"
#include <algorithm>
#include <iostream>
#include <utility>

namespace entities {
ChaseGhost::ChaseGhost(const float x, const float y, std::shared_ptr<Pacman> pacman,
                       const std::vector<std::vector<bool>>& wallgrid, const int id, const float chasetime)
    : Ghost(x, y, std::move(pacman), wallgrid, id, chasetime) {
    // Create a ghost and set its speed
    setSpeed(6.5f);
}

float ChaseGhost::distanceTurn(const std::vector<int> direction, const float dt) {
    if (dying)
        // If we are dying (eyes) Go back to startpos
        return BreathFirstDistance(direction, startpos, dt);
    // Else target the pacman Position (pacman->getPosition())
    return BreathFirstDistance(direction, pacman->getPosition(), dt);
}

void ChaseGhost::CalculateNextTurn(const float dt) {
    std::vector<int> direction;
    float best_distance = -1.f;
    std::vector<std::vector<int>> best_directions;

    // Calculate the closest distance if we were to take a certain direction
    for (const std::vector<int>& dir_try : IsAtIntersection()) {
        const float dis = distanceTurn(dir_try, dt);
        // Maximize or minimize based on feared or not
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
    // a little delay before checking if we are able to make turns again (prevents verry gittery behaviour at large
    // gaps)
    turnTimer = turnSpeed;
}
} // namespace entities