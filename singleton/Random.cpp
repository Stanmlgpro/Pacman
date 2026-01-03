//
// Created by stan1 on 10/11/2025.
//
#include "Random.h"
#include <random>

namespace singleton {
// initiate the distribution
Random::Random() : gen(std::random_device{}()) {}

Random& Random::getInstance() {
    // create a static variable so we always return the same object
    static Random instance;
    return instance;
}

int Random::get(int min, int max) {
    // return a random number between the boundaries using the ditribution
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}
} // namespace singleton
