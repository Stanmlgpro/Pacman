//
// Created by stan1 on 10/11/2025.
//

#ifndef RANDOM_H
#define RANDOM_H
#include <random>
/**
 * @file Random.h
 * @brief Random Class
 */
namespace singleton {
    /**
* @class Random
* @brief Class for Random Chance
*
* Singleton class used by entities to break ties and make decisions
*/
class Random {
private:
    /** random distribution to generate random numbers */
    std::mt19937 gen;
    /** keep the constructor private to prevent non-singleton behaviour */
    Random();

public:
    /** delete all other possible ways of creating more than 1 Random class */
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;
    /**
     * @brief Generates a random number
     *
     * based on the boundaries it generates a random number between them
     *
     * @param min minimal boundary
     * @param max maximal boundary
     * @return returns a random number between the boundaries
     */
    int get(int min, int max);
    /**
* @brief Gives back the Random object
*/
    static Random& getInstance();
};
} // namespace singleton

#endif // RANDOM_H
