//
// Created by stan1 on 13/11/2025.
//

#ifndef SFMLWORLDSOUNDS_H
#define SFMLWORLDSOUNDS_H
#include "WorldSound.h"
#include <SFML/Audio.hpp>
/**
 * @file SFMLWorldSounds.h
 * @brief SFMLWorldSounds Class
 */
namespace sounds {
    /**
* @class SFMLWorldSounds
* @brief derives from the WorldSound
*
* Implements all the pure virtual functions and plays specific SFML sounds
*/
class SFMLWorldSounds : public WorldSound {
public:
    /**
* @brief Creates an SFMLFactory object.
*
* Reads in all sound buffers and connects them to a playable sound
*/
    SFMLWorldSounds();

    /// Overrides WorldSound::Start
    void Start() override;
    /// Overrides WorldSound::OrbEaten
    void OrbEaten() override;
    /// Overrides WorldSound::PowerOrbEaten
    void PowerOrbEaten() override;
    /// Overrides WorldSound::FruitEaten
    void FruitEaten() override;
    /// Overrides WorldSound::GhostEaten
    void GhostEaten() override;
    /// Overrides WorldSound::FearMode
    void FearMode() override;
    /// Overrides WorldSound::EndFearMode
    void EndFearMode() override;
    /// Overrides WorldSound::PacmanDying
    void PacmanDying() override;
    /// Overrides WorldSound::EndGame
    void EndGame() override;

    ~SFMLWorldSounds() override;

private:
    /** buffers are filled and put in sf::Sound to play */
    /// @{
    sf::SoundBuffer startBuffer;
    sf::Sound startSound;
    sf::SoundBuffer munchBuffer;
    sf::Sound munchSound;
    sf::SoundBuffer munchpowerorbBuffer;
    sf::Sound munchpowerorbSound;
    sf::SoundBuffer munchFruitBuffer;
    sf::Sound munchFruitSound;
    sf::SoundBuffer ghosteatBuffer;
    sf::Sound ghosteatSound;
    sf::SoundBuffer fearBuffer;
    sf::Sound fearSound;
    sf::SoundBuffer pacmandieBuffer;
    sf::Sound pacmandieSound;
    sf::SoundBuffer ghostWalkBuffer;
    sf::Sound ghostWalkSound;
    /// @}
};
} // namespace sounds

#endif // SFMLWORLDSOUNDS_H
