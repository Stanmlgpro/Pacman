//
// Created by stan1 on 06/11/2025.
//

#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <chrono>
/**
 * @file Stopwatch.h
 * @brief Stopwatch Class
 */
namespace singleton {
    /**
* @class Stopwatch
* @brief Class for calculating the delta time
*
* Singleton class used by entities to update correctly
*/
class Stopwatch {
private:
    /** to keep track of the last update */
    std::chrono::high_resolution_clock::time_point lastTime;
    float deltaTime;
    /** keep the constructor private to prevent non-singleton behaviour */
    Stopwatch();
    /** for possible pausing of the timer */
    bool paused = false;

public:
    /** delete all other possible ways of creating more than 1 Stopwatch class */
    Stopwatch(const Stopwatch&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;
    /**
* @brief Gives back the Stopwatch object
*/
    static Stopwatch& getInstance();
    /**
* @brief pause the Stopwatch
*/
    void pause();
    /**
* @brief resume the Stopwatch
*/
    void resume();
    /**
* @brief calculates the dt based on the last update
*/
    void tick();
    /**
 * @return returns the DeltaTime (dt)
 */
    float getDeltaTime() const;
};
} // namespace singleton

#endif // STOPWATCH_H
