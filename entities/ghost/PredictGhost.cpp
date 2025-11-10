//
// Created by stan1 on 09/11/2025.
//

#include "PredictGhost.h"
#include <cmath>
#include "entities/Pacman.h"
#include <iostream>

PredictGhost::PredictGhost(float x, float y, std::shared_ptr<Pacman> pacman, const std::vector<std::vector<bool>>& wallgrid, int id) : Ghost(x, y, pacman, wallgrid, id) {
    speed = 8.f;
}

float PredictGhost::distanceTurn(std::vector<int> direction, float dt) {
    float newX = position.x + direction[0] * speed * dt;
    float newY = position.y + direction[1] * speed * dt;
    float newPacmanX = pacman->getPosition().x + pacman->getDirection()[0] * pacman->getSpeed() * 4 * dt;
    float newPacmanY = pacman->getPosition().y + pacman->getDirection()[1] * pacman->getSpeed() * 4 * dt;
    float dis = std::abs(newX - newPacmanX) + std::abs(newY - newPacmanY);
    return dis;
}

void PredictGhost::CalculateNextTurn(float dt) {
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

    std::cout << "calculated direction: " << direction[0] << ", " << direction[1] << std::endl;
    this->direction = direction;
}