//
// Created by stan1 on 13/11/2025.
//

#include "SFMLWorldSounds.h"
#include <iostream>

SFMLWorldSounds::SFMLWorldSounds() {
    if (!munchBuffer.loadFromFile("../sounds/munch_1.mp3")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }
    munchSound.setBuffer(munchBuffer);
}

void SFMLWorldSounds::OrbEaten() {
    munchSound.play();
}
