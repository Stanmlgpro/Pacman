//
// Created by stan1 on 09/11/2025.
//

#include "ChaseGhost.h"
#include "World.h"
#include "entities/Pacman.h"
#include <algorithm>
#include <iostream>

namespace entities {
ChaseGhost::ChaseGhost(float x, float y, std::shared_ptr<Pacman> pacman, const std::vector<std::vector<bool>>& wallgrid,
                       int id, float chasetime)
    : Ghost(x, y, pacman, wallgrid, id, chasetime) {
    // Create a ghost and set its speed
    setSpeed(6.5f);
}

float ChaseGhost::distanceTurn(std::vector<int> direction, float dt) {
    if (dying)
        // If we are dying (eyes) Go back to startpos
        return BreathFirstDistance(direction, startpos, dt);
    // Else target the pacman Position (pacman->getPosition())
    return BreathFirstDistance(direction, pacman->getPosition(), dt);
}

void ChaseGhost::CalculateNextTurn(float dt) {
    std::vector<int> direction;
    float best_distance = -1.f;
    std::vector<std::vector<int>> best_directions;

    // Calculate the closest distance if we were to take a certain direction
    for (const std::vector<int>& dir_try : IsAtIntersection()) {
        float dis = distanceTurn(dir_try, dt);
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
    // a little delay before checking if we are able to make turns again (prevents verry gittery behaviour at large gaps)
    turnTimer = turnSpeed;
}
} // namespace entities