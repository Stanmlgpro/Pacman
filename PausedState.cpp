//
// Created by stan on 10/14/25.
//

#include "StateManager.h"
#include "PausedState.h"
#include "LevelState.h"
#include "MenuState.h"

PausedState::PausedState(std::shared_ptr<StateManager> statemanager) {
    this->statemanager = statemanager;
    std::cout << "in a Paused state" << std::endl;
}

void PausedState::HandleEvent(const sf::Event &e) {
    if (e.type == sf::Event::KeyPressed) {
        if (e.key.code == sf::Keyboard::Escape) {
            std::cout << "going to menu screen" << std::endl;
            statemanager->PopState();
            statemanager->PopState();
        }
        else if (e.key.code == sf::Keyboard::Enter) {
            std::cout << "going to play the level again" << std::endl;
            statemanager->PopState();
        }
    }
}

void PausedState::Update(float dt) {
}

void PausedState::Render(sf::RenderWindow& window) {
}

PausedState::~PausedState() = default;