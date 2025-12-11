//
// Created by stan1 on 10/11/2025.
//
#include <random>
#include "Random.h"

namespace singleton {
    Random::Random() : gen(std::random_device{}()) {}

    Random& Random::getInstance() {
        static Random instance;
        return instance;
    }

    int Random::get(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(gen);
    }
}
