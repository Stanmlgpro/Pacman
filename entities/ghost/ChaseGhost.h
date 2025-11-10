//
// Created by stan1 on 09/11/2025.
//

#ifndef CHASEGHOST_H
#define CHASEGHOST_H
#include "entities/ghost/Ghost.h"

class ChaseGhost : public Ghost {
public:
    ChaseGhost(float x, float y, std::shared_ptr<Pacman> pacman, const std::vector<std::vector<bool>>& wallgrid, int id, float chasetime);

    float distanceTurn(std::vector<int> direction, float dt) override;
    void CalculateNextTurn(float dt) override;
};



#endif //CHASEGHOST_H
