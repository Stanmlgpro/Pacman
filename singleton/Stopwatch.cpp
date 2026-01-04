//
// Created by stan1 on 06/11/2025.
//

#include "Stopwatch.h"

namespace singleton {
Stopwatch::Stopwatch() {
    // initiate the variables
    lastTime = std::chrono::high_resolution_clock::now();
    deltaTime = 0.f;
}

Stopwatch& Stopwatch::getInstance() {
    // create a static variable so we always return the same object
    static Stopwatch instance;
    return instance;
}

void Stopwatch::tick() {
    // recalculate the delta time and the lastname variables
    const auto now = std::chrono::high_resolution_clock::now();
    deltaTime = std::chrono::duration<float>(now - lastTime).count();
    lastTime = now;
}

float Stopwatch::getDeltaTime() const {
    // return the delta time if we are not paused
    if (paused)
        return 0.f;
    return deltaTime;
}
// simple setters
void Stopwatch::pause() { paused = true; }
void Stopwatch::resume() { paused = false; }
} // namespace singleton