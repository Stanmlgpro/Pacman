//
// Created by stan1 on 13/10/2025.
//

#ifndef ENTITY_H
#define ENTITY_H
#include "../entities/Position.h"
#include <memory>
#include <vector>

#include "../singleton/Random.h"
#include "./views/View.h"
/**
 * @file Entity.h
 * @brief Entity Class
 */
class World;
namespace entities {

class Wall;
class Orb;
class PowerOrb;
class Ghost;
class Pacman;
class Fruit;
/**
 * @class Entity
 * @brief Main Entity class
 *
 * Parent class of ALL entities implements update function and basic setters/getters
 */
class Entity {
public:
    /**
     * @brief Creates a Entity object.
     *
     * default constructor for entites that dont need as much information to work
     */
    Entity() = default;
    /**
     * @brief Creates a Entity object.
     *
     * default constructor for entites that dont need as much information to work
     *
     * @param mapwidth width of the map to calculate positions and speed
     * @param mapheight height of the map to calculate positions and speed
     */
    Entity(int mapwidth, int mapheight);
    /**
     * @brief Function that wraps Position coordinates
     *
     * functions that wraps the coordinates to the width, height to allow for tunnels from one side to the other
     *
     * @param v float to wrap
     *
     * @return new float after wrapping
     */
    static float wrap(float v);
    /**
     * @brief updates the entity
     *
     * overrwritten by every entity, is called every frame with dt.
     * Used to update the position, timers, view of every entity in the level
     *
     * @param dt delta time between calls
     */
    virtual void Update(float dt) = 0;

    /**
     * @brief draws the view
     *
     * checks for the existence of a way to visualize the entity and updates it if present
     */
    void Draw() const;
    /**
     * @brief Function to check for collisions
     *
     * function that is called every frame that is overwritten by every entity.
     * All children callback to the World so we know wich Class is interacting with pacman
     *
     * @param world used for callback
     *
     * @return returns entities that have to be deleted after possible interaction
     */
    virtual std::shared_ptr<Entity> Interact(World& world) = 0;
    /**
     * @brief Sets the view
     * @param view
     */
    void setView(std::unique_ptr<views::View> view);
    /** used by ghost class, present for overriding possibilities */
    virtual void setFeared(bool feared) {}
    /** used by ghost class, present for overriding possibilities */
    virtual bool getFeared() { return true; }
    /** used by ghost class, present for overriding possibilities */
    virtual float getFearCheck() const { return 0.f; }
    /** used by ghost, pacman class, present for overriding possibilities */
    virtual void reset() {}
    /**
     * @brief check to see if the level is won
     *
     * calls the function on all entities and based on the check bool it decides if the game is won or not.
     * true = won, false = continue
     *
     * @param check passed by reference so it can be changed
     */
    virtual void checkWin(bool& check) {};
    /** used by ghost, pacman class, present for overriding possibilities */
    virtual bool getDying() const { return false; }

    Position getPosition() const;
    /**
     * @brief Sets the Position
     * @param x x part of the position
     * @param y y part of the position
     */
    void setPosition(float x, float y);
    /**
     * @return returns the direction
     */
    std::vector<int> getDirection() const;
    /**
     * @brief Sets the Direction
     * @param direction
     */
    void setDirection(std::vector<int> direction);
    /**
     * @return returns the collision
     */
    float getCollsionSize() const;
    /**
     * @brief Sets the CollisionSize
     * @param size
     */
    void setCollisionSize(float size);
    virtual ~Entity() = default;

protected:
    Position position{};
    std::vector<int> direction;
    std::unique_ptr<views::View> view;
    int mapwidth;
    int mapheight;
    /** used by entities to break ties and make decisions */
    singleton::Random& random = singleton::Random::getInstance();
    float CollisionSize = 0.0f;
};
} // namespace entities

#endif // ENTITY_H
