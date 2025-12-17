//
// Created by stan1 on 13/11/2025.
//

#include "SFMLWorldSounds.h"
#include <iostream>

namespace sounds {
SFMLWorldSounds::SFMLWorldSounds() {
    if (!startBuffer.loadFromFile("../sounds/pacman_beginning.wav")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }
    startSound.setBuffer(startBuffer);
    if (!munchBuffer.loadFromFile("../sounds/munch_1.mp3")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }
    munchSound.setBuffer(munchBuffer);
    if (!munchpowerorbBuffer.loadFromFile("../sounds/pacman_eatpowerpellet.wav")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }
    munchpowerorbSound.setBuffer(munchpowerorbBuffer);
    if (!munchFruitBuffer.loadFromFile("../sounds/pacman_eatfruit.mp3")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }
    munchFruitSound.setBuffer(munchFruitBuffer);
    if (!ghosteatBuffer.loadFromFile("../sounds/pacman_eatghost.wav")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }
    ghosteatSound.setBuffer(ghosteatBuffer);
    if (!fearBuffer.loadFromFile("../sounds/fearmode.mp3")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }
    fearSound.setBuffer(fearBuffer);
    fearSound.setLoop(true);
    if (!pacmandieBuffer.loadFromFile("../sounds/pacman_death.wav")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }
    pacmandieSound.setBuffer(pacmandieBuffer);
    if (!ghostWalkBuffer.loadFromFile("../sounds/ghostMove.mp3")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }
    ghostWalkSound.setBuffer(ghostWalkBuffer);
    ghostWalkSound.setLoop(true);
}

void SFMLWorldSounds::Start() { startSound.play(); ghostWalkSound.play(); }
void SFMLWorldSounds::OrbEaten() { munchSound.play(); }
void SFMLWorldSounds::PowerOrbEaten() { munchpowerorbSound.play(); }
void SFMLWorldSounds::FruitEaten() { munchFruitSound.play(); }
void SFMLWorldSounds::GhostEaten() { ghosteatSound.play(); }
void SFMLWorldSounds::FearMode() { fearSound.play(); ghostWalkSound.stop(); }
void SFMLWorldSounds::EndFearMode() { fearSound.stop(); ghostWalkSound.play(); }
void SFMLWorldSounds::PacmanDying() { pacmandieSound.play(); }
void SFMLWorldSounds::EndGame() { ghostWalkSound.stop(); fearSound.stop();}

SFMLWorldSounds::~SFMLWorldSounds() = default;
} // namespace sounds