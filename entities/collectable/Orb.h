//
// Created by stan on 10/15/25.
//

#ifndef PACMAN_ORB_H
#define PACMAN_ORB_H
#include "./entities/Entity.h"
/**
 * @file Orb.h
 * @brief Orb Class
 */
namespace entities {
/**
 * @class Orb
 * @brief Orb class to create basic Pacman orbs
 *
 * Collectable for Pacman that gives scoring and one that must be collected before resetting.
 */
class Orb : public Entity, public std::enable_shared_from_this<Orb> {
public:
    /**
 * @brief Creates a Orb object.
 * @param x X Position
 * @param y Y Position
 */
    Orb(float x, float y);

    /// Override Entity::Interact
    std::shared_ptr<Entity> Interact(World& world) override;
    /// Override Entity::Update
    void Update(float dt) override;
    /// Override Entity::checkWin
    void checkWin(bool& check) override;

    ~Orb() override = default;
};
} // namespace entities

#endif // PACMAN_ORB_H