//
// Created by stan1 on 09/11/2025.
//

#ifndef LOCKEDGHOST_H
#define LOCKEDGHOST_H
#include "entities/ghost/Ghost.h"
/**
 * @file LockedGhost.h
 * @brief LockedGhost Class
 */
namespace entities {
/**
 * @class LockedGhost
 * @brief LockedGhost class to add a ghost type
 *
 * 1 of 3 types of Ghost, this one takes a random direction on each intersection it faces
 */
class LockedGhost : public Ghost {
public:
    /**
     * @brief Creates a PowerOrb object.
     * @param x X Position
     * @param y Y Position
     * @param pacman pacman object to get its status
     * @param wallgrid 2D vector of bools that represent the existing walls, used to prevent phasing trough them
     * @param id in (1,2,3,4) decides when a ghost can start chasing pacman
     * @chasetime time since spawning in that ghost has to wait before moving
     */
    LockedGhost(float x, float y, std::shared_ptr<Pacman> pacman, const std::vector<std::vector<bool>>& wallgrid,
                int id, float chasetime);

    /// Overrides Ghost::distanceTurn
    float distanceTurn(std::vector<int> direction, float dt) override;
    /// Overrides Ghost::CalculateNextTurn
    void CalculateNextTurn(float dt) override;
};
} // namespace entities

#endif // LOCKEDGHOST_H
