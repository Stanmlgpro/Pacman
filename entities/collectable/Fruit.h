//
// Created by stan1 on 12/12/2025.
//

#ifndef FRUIT_H
#define FRUIT_H
#include "./entities/Entity.h"
/**
 * @file Fruit.h
 * @brief Fruit Class and all its Children
 */
namespace entities {
/**
 * @class Fruit
 * @brief Fruit class to inherit from to have different Scoring and Views for each.
 *
 * Collectable for Pacman that gives scoring.
 */
class Fruit : public Entity {
public:
    /**
     * @brief Creates a Fruit object.
     * @param x X Position
     * @param y Y Position
     */
    Fruit(float x, float y);

    /// Overrides Entity::Update
    void Update(float dt) override;

    ~Fruit() override = default;
};
/**
 * @class Cherry
 * @brief Cherry fruit
 */
class Cherry : public Fruit, public std::enable_shared_from_this<Cherry> {
public:
    Cherry(float x, float y);
    /// Overrides Entity::Interact
    std::shared_ptr<Entity> Interact(World& world) override;
};
/**
 * @class Strawberry
 * @brief Strawberry fruit
 */
class Strawberry : public Fruit, public std::enable_shared_from_this<Strawberry> {
public:
    Strawberry(float x, float y);
    /// Overrides Entity::Interact
    std::shared_ptr<Entity> Interact(World& world) override;
};
/**
 * @class Orange
 * @brief Orange fruit
 */
class Orange : public Fruit, public std::enable_shared_from_this<Orange> {
public:
    Orange(float x, float y);
    /// Overrides Entity::Interact
    std::shared_ptr<Entity> Interact(World& world) override;
};
/**
 * @class Apple
 * @brief Apple fruit
 */
class Apple : public Fruit, public std::enable_shared_from_this<Apple> {
public:
    Apple(float x, float y);
    /// Overrides Entity::Interact
    std::shared_ptr<Entity> Interact(World& world) override;
};
/**
 * @class Melon
 * @brief Melon fruit
 */
class Melon : public Fruit, public std::enable_shared_from_this<Melon> {
public:
    Melon(float x, float y);
    /// Overrides Entity::Interact
    std::shared_ptr<Entity> Interact(World& world) override;
};
/**
 * @class Galaxian
 * @brief Galaxian fruit
 */
class Galaxian : public Fruit, public std::enable_shared_from_this<Galaxian> {
public:
    Galaxian(float x, float y);
    /// Overrides Entity::Interact
    std::shared_ptr<Entity> Interact(World& world) override;
};
/**
 * @class Bell
 * @brief Bell fruit
 */
class Bell : public Fruit, public std::enable_shared_from_this<Bell> {
public:
    Bell(float x, float y);
    /// Overrides Entity::Interact
    std::shared_ptr<Entity> Interact(World& world) override;
};
/**
 * @class Key
 * @brief Key fruit
 */
class Key : public Fruit, public std::enable_shared_from_this<Key> {
public:
    Key(float x, float y);
    /// Overrides Entity::Interact
    std::shared_ptr<Entity> Interact(World& world) override;
};
} // namespace entities

#endif // FRUIT_H
