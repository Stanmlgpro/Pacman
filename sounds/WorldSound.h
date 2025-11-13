//
// Created by stan1 on 13/11/2025.
//

#ifndef WORLDSOUND_H
#define WORLDSOUND_H
#include <SFML/Audio.hpp>


class WorldSound {
public:
    virtual void OrbEaten() = 0;
    virtual void GhostEaten() = 0;
    virtual void FearMode() = 0;
    virtual void PacmanDying () = 0;
};



#endif //WORLDSOUND_H
