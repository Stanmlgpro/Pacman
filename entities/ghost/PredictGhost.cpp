//
// Created by stan1 on 09/11/2025.
//

#include "PredictGhost.h"
#include "entities/Pacman.h"
#include <cmath>
#include <iostream>

namespace entities {
PredictGhost::PredictGhost(float x, float y, std::shared_ptr<Pacman> pacman,
                           const std::vector<std::vector<bool>>& wallgrid, int id, float chasetime)
    : Ghost(x, y, pacman, wallgrid, id, chasetime) {
    // Create a ghost and set its speed
    setSpeed(6.5f);
}

float PredictGhost::distanceTurn(std::vector<int> direction, float dt) {
    if (dying)
        // If we are dying (eyes) Go back to startpos
        return BreathFirstDistance(direction, startpos, dt);
    if (feared)
        // If feared run from pacman (distance will be maximized when calling this instead of minimized)
        return BreathFirstDistance(direction, pacman->getPosition(), dt);
    // Predict pacman by minimizing the distance between us and a position infront of pacman
    float newPacmanX = pacman->getPosition().x + pacman->getDirection()[0] * pacman->getSpeed() * 4 * dt;
    float newPacmanY = pacman->getPosition().y + pacman->getDirection()[1] * pacman->getSpeed() * 4 * dt;
    return BreathFirstDistance(direction, Position{newPacmanX, newPacmanY}, dt);
}

void PredictGhost::CalculateNextTurn(float dt) {
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
    // a little delay before checking if we are able to make turns again (prevents verry gittery behaviour at large
    // gaps)
    turnTimer = turnSpeed;
}
} // namespace entities