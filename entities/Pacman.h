//
// Created by stan on 10/15/25.
//

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "Entity.h"
/**
 * @file Pacman.h
 * @brief Pacman Class
 */
namespace entities {
/**
 * @class Pacman
 * @brief Main Pacman class, main character of the levels
 *
 * Controls the main character of our game
 */
class Pacman : public Entity, public std::enable_shared_from_this<Pacman> {
public:
    /**
     * @brief Creates a PowerOrb object.
     * @param speed speed at which pacman will move
     * @param mapwidth width of the map, used for calculation
     * @param mapheight height of the map, used for calculation
     * @param x X Position
     * @param y Y Position
     */
    Pacman(float speed, int mapwidth, int mapheight, float x, float y);
    /**
     * @brief exists since all entites must override it but should not be called
     */
    std::shared_ptr<Entity> Interact(World& world) override;
    /**
     * @brief moves pacman Up
     */
    void Up();
    /**
     * @brief moves pacman Down
     */
    void Down();
    /**
     * @brief moves pacman Left
     */
    void Left();
    /**
     * @brief moves pacman Right
     */
    void Right();
    /// Overrides Entity::Update
    void Update(float dt) override;
    /**
     * @brief Sets Lives
     * @param lives
     */
    void setLives(int lives);
    /**
     * @brief Sets if we are allowed to move
     * @param moving
     */
    void setMoving(bool moving);
    /**
     * @return return Lives
     */
    int getLives() const;
    /**
     * @brief Sets the buffered direction
     * @param buffer
     */
    void setDirectionBuffer(std::vector<int> buffer);
    /**
     * @return return the buffered direction
     */
    std::vector<int> getDirectionBuffer() const;
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
     * @brief Sets if we are dying
     * @param dying
     */
    void setDying(bool dying);
    /**
     * @return returns Speed
     */
    bool getDying() const override;
    /**
     * @brief Sets if we are dead
     * @param dead
     */
    void setDead(bool dead);
    /**
     * @return returns whether we are dead
     */
    bool isDead() const;
    /**
     * @return returns whether we are damageable
     */
    bool isDamagable() const;
    /**
     * @brief resets pacman
     *
     * returns pacman to its original position, directions and resets all timers
     */
    void reset() override;

    ~Pacman() override = default;

private:
    /** buffer used for smoother direction changing, holds last inputted direction request */
    std::vector<int> direction_buffer;
    bool moving = true;
    int lives = 3;
    float speed;
    Position startpos;
    bool dying = false;
    bool dead = false;
    float dying_time = 0.f;
    /** used to make pacman invincible for a tiny while after dying to prevent instant loss */
    float invincibility_timer = 0.f;
    float invincibility_duration = 0.01f;
    bool damagable = true;
};
} // namespace entities

#endif // PACMAN_PACMAN_H