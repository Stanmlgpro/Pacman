//
// Created by stan1 on 13/11/2025.
//

#ifndef SFMLWORLDSOUNDS_H
#define SFMLWORLDSOUNDS_H
#include "WorldSound.h"


class SFMLWorldSounds : public WorldSound {
public:
    SFMLWorldSounds();

    void OrbEaten() override;
    void GhostEaten() override {}
    void FearMode() override {}
    void PacmanDying() override {}

private:
    sf::SoundBuffer munchBuffer;
    sf::Sound munchSound;
};



#endif //SFMLWORLDSOUNDS_H
