//
// Created by stan1 on 09/11/2025.
//

#include "PredictGhost.h"
#include <cmath>
#include "entities/Pacman.h"
#include <iostream>

PredictGhost::PredictGhost(float x, float y, std::shared_ptr<Pacman> pacman, const std::vector<std::vector<bool>>& wallgrid, int id, float chasetime) : Ghost(x, y, pacman, wallgrid, id, chasetime) {
    speed = 6.5f;

}

float PredictGhost::distanceTurn(std::vector<int> direction, float dt) {
    if (feared) {
        float newX = position.x + direction[0] * speed * dt;
        float newY = position.y + direction[1] * speed * dt;
        float dis = std::abs(newX - pacman->getPosition().x) + std::abs(newY - pacman->getPosition().y);
        return dis;
    }
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
    if (best_directions.empty()) return;
    if (best_directions.size() == 1) this->direction = best_directions[0];
    else this->direction = best_directions[random.get(0, best_directions.size() - 1)];
    turnTimer = turnSpeed;
}