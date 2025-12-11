//
// Created by stan1 on 13/11/2025.
//

#ifndef SFMLWORLDSOUNDS_H
#define SFMLWORLDSOUNDS_H
#include "WorldSound.h"
#include <SFML/Audio.hpp>

namespace sounds {
    class SFMLWorldSounds : public WorldSound {
    public:
        SFMLWorldSounds();

        void Start() override;
        void OrbEaten() override;
        void FruitEaten() override;
        void GhostEaten() override;
        void FearMode() override;
        void EndFearMode() override;
        void PacmanDying() override;

    private:
        sf::SoundBuffer startBuffer;
        sf::Sound startSound;
        sf::SoundBuffer munchBuffer;
        sf::Sound munchSound;
        sf::SoundBuffer munchfruitBuffer;
        sf::Sound munchfruitSound;
        sf::SoundBuffer ghosteatBuffer;
        sf::Sound ghosteatSound;
        sf::SoundBuffer fearBuffer;
        sf::Sound fearSound;
        sf::SoundBuffer pacmandieBuffer;
        sf::Sound pacmandieSound;
    };
}


#endif //SFMLWORLDSOUNDS_H
