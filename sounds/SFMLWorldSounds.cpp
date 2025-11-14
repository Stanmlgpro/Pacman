//
// Created by stan1 on 13/11/2025.
//

#include "SFMLWorldSounds.h"
#include <iostream>

SFMLWorldSounds::SFMLWorldSounds() {
    if (!startBuffer.loadFromFile("../sounds/pacman_beginning.wav")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }
    startSound.setBuffer(startBuffer);
    if (!munchBuffer.loadFromFile("../sounds/munch_1.mp3")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }
    munchSound.setBuffer(munchBuffer);
    if (!munchfruitBuffer.loadFromFile("../sounds/pacman_eatfruit.wav")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }
    munchfruitSound.setBuffer(munchfruitBuffer);
    if (!ghosteatBuffer.loadFromFile("../sounds/pacman_eatghost.wav")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }
    ghosteatSound.setBuffer(ghosteatBuffer);
    if (!fearBuffer.loadFromFile("../sounds/pacman_extrapac.wav")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }
    fearSound.setBuffer(fearBuffer);
    fearSound.setLoop(true);
    if (!pacmandieBuffer.loadFromFile("../sounds/pacman_death.wav")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }
    pacmandieSound.setBuffer(pacmandieBuffer);
}

void SFMLWorldSounds::Start() {
    startSound.play();
}
void SFMLWorldSounds::OrbEaten() {
    munchSound.play();
}
void SFMLWorldSounds::FruitEaten() {
    munchfruitSound.play();
}
void SFMLWorldSounds::GhostEaten() {
    ghosteatSound.play();
}
void SFMLWorldSounds::FearMode() {
    if (fearSound.getStatus() != sf::Sound::Playing) fearSound.play();
}
void SFMLWorldSounds::EndFearMode() {
    fearSound.stop();
}
void SFMLWorldSounds::PacmanDying() {
    pacmandieSound.play();
}
