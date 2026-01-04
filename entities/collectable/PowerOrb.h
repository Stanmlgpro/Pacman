//
// Created by stan1 on 11/12/2025.
//

#ifndef POWERORB_H
#define POWERORB_H
#include "./entities/Entity.h"
/**
 * @file PowerOrb.h
 * @brief PowerOrb Class
 */
namespace entities {
/**
 * @class PowerOrb
 * @brief PowerOrb class to create orbs that activate Fearmode
 *
 * Collectable for Pacman that gives scoring and one that must be collected before resetting.
 */
class PowerOrb final : public Entity, public std::enable_shared_from_this<PowerOrb> {
public:
    /**
     * @brief Creates a PowerOrb object.
     * @param x X Position
     * @param y Y Position
     */
    PowerOrb(float x, float y);

    /// Override Entity::Interact
    std::shared_ptr<Entity> Interact(World& world) override;

    /// Override Entity::Update
    void Update(float dt) override;
    /// Override Entity::checkWin
    void checkWin(bool& check) override;

    ~PowerOrb() override = default;
};
} // namespace entities

#endif // POWERORB_H
