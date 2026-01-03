//
// Created by stan1 on 10/11/2025.
//

#ifndef SCORE_H
#define SCORE_H
#include "factory/Sprite_IDs.h"
#include <string>
/**
 * @file Score.h
 * @brief Score Class
 */
/**
 * @class Score
 * @brief class responsible for the Score in the game
 */
class Score {
public:
    /**
     * @brief Creates a Score object.
     * @param player player playing the game
     */
    explicit Score(std::string player);
    /**
     * @brief adds points for eating an orb
     */
    void orbEaten();
    /**
     * @brief adds points for eating a PowerOrbEaten
     */
    void PowerOrbEaten();
    /**
     * @brief adds points for eating a specific type of fruit
     * @param ID used to identify each type of fruit
     */
    void FruitEaten(sprites::Sprite_ID ID);
    /**
     * @brief adds points for eating a ghost
     * @param combo used to add more and more scoring if ghost are eaten in rapid succession
     */
    void ghostEaten(int combo);
    /**
     * @brief adds points for completing a level
     */
    void levelWon();
    /**
     * @return returns the number of points the player has
     */
    int getPoints() const;
    /**
     * @brief wrights the score to a file
     *
     * uses the player to write his score to the scoreboard file if its high enough
     */
    void wright();
    /**
     * @brief resets the score to 0
     */
    void reset();
    /**
     * @brief Updates the score timers
     *
     * updates all the timers to check for fast succession of ghost eating
     * and if we have eaten an orb recently enough to not start deducing score
     *
     * @param dt amount to change the timers
     */
    void Update(float dt);

    ~Score();

private:
    int score;
    std::string player;
    /** used to check if the player is still eating orbs fast enough before deducing scoring */
    float last_orb_eaten = 0.f;
    float decrease_timer = 0.f;
};

#endif // SCORE_H
