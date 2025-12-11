//
// Created by stan1 on 10/11/2025.
//

#ifndef RANDOM_H
#define RANDOM_H
#include <random>

namespace singleton {
    class Random {
    private:
        std::mt19937 gen;

        Random();
    public:
        Random(const Random&) = delete;
        Random& operator=(const Random&) = delete;

        int get(int min, int max);

        static Random& getInstance();
    };
}


#endif //RANDOM_H
