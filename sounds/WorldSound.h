//
// Created by stan1 on 13/11/2025.
//

#ifndef WORLDSOUND_H
#define WORLDSOUND_H
/**
 * @file WorldSound.h
 * @brief WorldSound Class
 */
namespace sounds {
    /**
* @class WorldSound
* @brief Base class to derive from and implement
*
* Basic framework to play sounds
*/
class WorldSound {
public:
    /**
* @brief plays/ends the correct sound based on the requested function
*/
    /// @{
    virtual void Start() = 0;
    virtual void OrbEaten() = 0;
    virtual void PowerOrbEaten() = 0;
    virtual void FruitEaten() = 0;
    virtual void GhostEaten() = 0;
    virtual void FearMode() = 0;
    virtual void EndFearMode() = 0;
    virtual void PacmanDying() = 0;
    virtual void EndGame() = 0;
    /// @}

    virtual ~WorldSound() = default;
};
} // namespace sounds

#endif // WORLDSOUND_H
