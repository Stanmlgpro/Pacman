//
// Created by stan on 10/15/25.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "entities/Entity.h"
/**
 * @file Ghost.h
 * @brief Ghost Class
 */
namespace entities {
/**
 * @class Ghost
 * @brief Main ghost class
 *
 * Parent Ghost class to add al basic behaviour of ghosts
 */
class Ghost : public Entity, public std::enable_shared_from_this<Ghost> {
public:
    /**
     * @brief Creates a Ghost object.
     * @param x X Position
     * @param y Y Position
     * @param pacman pacman object to get its status
     * @param wallgrid 2D vector of bools that represent the existing walls, used to prevent phasing trough them
     * @param id in (1,2,3,4) decides when a ghost can start chasing pacman
     * @param chasetime time since spawning in that ghost has to wait before moving
     */
    Ghost(float x, float y, std::shared_ptr<Pacman> pacman, const std::vector<std::vector<bool>>& wallgrid, int id,
          float chasetime);
    /**
     * @brief Calculates the ManhattanDistance
     *
     * from our position (with a specific direction added) to a target position
     *
     * @param direction direction we take before calculating the distance
     * @param target target we want to chase
     * @param dt amount we move in the direction
     * @return returns the distance using the manhattandistance algorithm
     */
    float ManhattanDistance(std::vector<int> direction, Position target, float dt);
    /**
     * @brief Helper function
     *
     * A helper function to find the BFS distance using the wallgrid
     *
     * @param startX start position of X
     * @param startY start position of Y
     * @param targetX end position of X
     * @param targetY end position of Y
     * @return returns the distance using the BreathFirstDistance algorithm
     */
    int BFSGridDistance(int startX, int startY, int targetX, int targetY) const;
    /**
     * @brief Calculates the BreathFirstDistance
     *
     * from our position (with a specific direction added) to a target position
     *
     * @param direction direction we take before calculating the distance
     * @param target target we want to chase
     * @param dt amount we move in the direction
     * @return returns the distance using the BreathFirstDistance algorithm
     */
    float BreathFirstDistance(std::vector<int> direction, Position target, float dt);
    /**
     * @brief Function to see available directions
     *
     * checks all directions and chooses all the possible, then also chooses if we are at a valid intersection
     *
     * @return returns all valid directions to check
     */
    std::vector<std::vector<int>> IsAtIntersection() const;
    /**
     * @brief Calculates the distance when taking a specific turn
     *
     * child classes well override this to choose their own way of calculation the desired direction with the desired
     * algorithm
     *
     * @param direction direction we take before calculating the distance
     * @param dt amount we move in the direction
     * @return returns the distance using the specified algorithm and target of the child class
     */
    virtual float distanceTurn(std::vector<int> direction, float dt) = 0;
    /**
     * @brief Calculates the next turn our ghost will take
     *
     * uses the other previous function to override from and come to a conclusion of wich direction our ghost shall take
     *
     * @return sets private direction variable of ghost child class to use in the update function
     */
    virtual void CalculateNextTurn(float dt) = 0;

    /// Overrides from Entity::Interact
    std::shared_ptr<Entity> Interact(World& world) override;
    /// Overrides from Entity::Update
    void Update(float dt) override;

    /**
     * @brief Sets fearmode
     * @param feared
     */
    void setFeared(bool feared);
    /**
     * @return if we are feared or not
     */
    bool getFeared();
    /**
     * @return counter that checks the time we are in fearmode
     */
    float getFearCheck() const override;
    /**
     * @return returns the position the ghost was originally spawned on
     */
    Position getStartPos() const;
    /**
     * @return returns the ID
     */
    int getId() const;
    /**
     * @brief Calculates new Dt
     *
     * sets dt to the correct value based on mapwidth and maplength and the speed at which we are moving
     *
     * @param dt the old delta time
     * @return the newly calculated dt
     */
    float MoveDt(float dt) const;
    /**
     * @brief Sets Speed
     * @param speed
     */
    void setSpeed(float speed);
    /**
     * @return returns the Speed
     */
    float getSpeed() const;
    /**
     * @brief Sets FearTime
     * @param feartime
     */
    void setFearTime(float feartime);
    /**
     * @return returns the Dying boolean value
     */
    bool getDying() const override;
    /**
     * @brief Sets wether are not we are in the dying state (Right before actually being dead)
     * @param dying
     */
    void setDying(bool dying);
    /**
     * @brief resets the ghost
     *
     * returns ghost to their original position, directions and resets all timers
     */
    void reset() override;

    ~Ghost() override = default;

protected:
    std::shared_ptr<Pacman> pacman;
    /** 2D grid of boolean values to check the position off walls efficiently */
    std::vector<std::vector<bool>> wallgrid;
    Position startpos;
    bool feared = false;
    /** time fearmode is active */
    float feartime = 6.f;
    /** timer that checks if fearmode must be ended */
    float fearcheck = 0.f;
    int id;
    float speed;
    float original_speed;
    /** time we cannot chase after spawning in */
    float ChaseTime;
    /** timer that checks time past after spawning to activate chase mode once needed */
    float ChaseTimer;
    bool Chasing;
    /** delay after turning to prevent gittery behaviour in large gaps */
    float turnSpeed = 0.1f;
    float turnTimer = 0.f;
    bool dying = false;
};
} // namespace entities

#endif // PACMAN_GHOST_H