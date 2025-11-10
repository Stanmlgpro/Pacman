//
// Created by stan1 on 06/11/2025.
//

#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <chrono>

class Stopwatch {
private:
    std::chrono::high_resolution_clock::time_point lastTime;
    float deltaTime;

    Stopwatch();
    bool paused = false;
public:
    Stopwatch(const Stopwatch&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;

    static Stopwatch& getInstance();

    void pause();
    void resume();
    void tick();

    float getDeltaTime() const;
};



#endif //STOPWATCH_H
