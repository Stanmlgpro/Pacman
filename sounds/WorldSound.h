//
// Created by stan1 on 13/11/2025.
//

#ifndef WORLDSOUND_H
#define WORLDSOUND_H

namespace sounds {
class WorldSound {
public:
    virtual void Start() = 0;
    virtual void OrbEaten() = 0;
    virtual void PowerOrbEaten() = 0;
    virtual void FruitEaten() = 0;
    virtual void GhostEaten() = 0;
    virtual void FearMode() = 0;
    virtual void EndFearMode() = 0;
    virtual void PacmanDying() = 0;
};
} // namespace sounds

#endif // WORLDSOUND_H
