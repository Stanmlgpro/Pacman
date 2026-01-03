//
// Created by stan on 10/15/25.
//

#ifndef PACMAN_WALL_H
#define PACMAN_WALL_H
#include "Entity.h"
/**
 * @file Wall.h
 * @brief Wall Class
 */
namespace entities {
/**
 * @class Wall
 * @brief Wall class to create the boundaries
 */
class Wall : public Entity, public std::enable_shared_from_this<Wall> {
public:
    /**
     * @brief Creates a Wall object.
     * @param x X Position
     * @param y Y Position
     */
    Wall(float x, float y);

    /// Override Entity::Interact
    std::shared_ptr<Entity> Interact(World& world) override;
    /// Override Entity::Update
    void Update(float dt) override;

    ~Wall() override = default;
};
} // namespace entities

#endif // PACMAN_WALL_H