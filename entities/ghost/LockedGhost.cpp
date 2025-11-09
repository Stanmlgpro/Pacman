//
// Created by stan1 on 09/11/2025.
//

#include "LockedGhost.h"

LockedGhost::LockedGhost(float x, float y, std::shared_ptr<Pacman> pacman, const std::vector<std::vector<bool>>& wallgrid, int id) : Ghost(x, y, pacman, wallgrid, id) {}

float LockedGhost::tryTurn(std::vector<int> direction, float dt) {
    return 0.f;
}

float LockedGhost::distanceTurn(std::vector<int> direction, float dt) {
    return 0.f;
}

void LockedGhost::CalculateNextTurn(float dt) {
    return;
}