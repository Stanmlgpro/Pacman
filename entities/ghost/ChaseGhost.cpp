//
// Created by stan1 on 09/11/2025.
//

#include "ChaseGhost.h"

ChaseGhost::ChaseGhost(float x, float y, std::shared_ptr<Pacman> pacman, const std::vector<std::vector<bool>>& wallgrid, int id) : Ghost(x, y, pacman, wallgrid, id) {}

float ChaseGhost::distanceTurn(std::vector<int> direction, float dt) {
    return 0.f;
}

void ChaseGhost::CalculateNextTurn(float dt) {
    return;
}
