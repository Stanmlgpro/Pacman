//
// Created by stan1 on 06/11/2025.
//

#include "Stopwatch.h"

Stopwatch::Stopwatch() {
    lastTime = std::chrono::high_resolution_clock::now();
    deltaTime = 0.f;
}

Stopwatch& Stopwatch::getInstance() {
    static Stopwatch instance;
    return instance;
}

void Stopwatch::tick() {
    auto now = std::chrono::high_resolution_clock::now();
    deltaTime = std::chrono::duration<float>(now - lastTime).count();
    lastTime = now;
}

float Stopwatch::getDeltaTime() const {
    return deltaTime;
}