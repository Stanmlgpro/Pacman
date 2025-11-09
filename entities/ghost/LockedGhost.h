//
// Created by stan1 on 09/11/2025.
//

#ifndef LOCKEDGHOST_H
#define LOCKEDGHOST_H
#include "entities/ghost/Ghost.h"

class LockedGhost : public Ghost {
public:
    LockedGhost(float x, float y, std::shared_ptr<Pacman> pacman, const std::vector<std::vector<bool>>& wallgrid, int id);

    float distanceTurn(std::vector<int> direction, float dt) override;
    void CalculateNextTurn(float dt) override;
};



#endif //LOCKEDGHOST_H
