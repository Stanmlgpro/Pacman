//
// Created by stan1 on 09/11/2025.
//

#include "PredictGhost.h"

PredictGhost::PredictGhost(float x, float y, std::shared_ptr<Pacman> pacman, const std::vector<std::vector<bool>>& wallgrid, int id) : Ghost(x, y, pacman, wallgrid, id) {}

float PredictGhost::tryTurn(std::vector<int> direction, float dt) {
    return 0.f;
}

float PredictGhost::distanceTurn(std::vector<int> direction, float dt) {
    return 0.f;
}

void PredictGhost::CalculateNextTurn(float dt) {
    return;
}