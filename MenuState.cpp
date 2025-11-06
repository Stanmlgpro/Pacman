//
// Created by stan on 10/14/25.
//

#include "MenuState.h"
#include "StateManager.h"
#include "LevelState.h"

MenuState::MenuState(std::shared_ptr<StateManager> statemanager) {
    this->statemanager = statemanager;
}

void MenuState::HandleEvent(const sf::Event &e) {
    if (e.type == sf::Event::KeyPressed) {
        if (e.key.code == sf::Keyboard::Enter) {
            std::cout << "making new level" << std::endl;
            statemanager->PushState(LEVEL);
        }
    }
}

void MenuState::Update() {}

void MenuState::Render(sf::RenderWindow& window) {
}

MenuState::~MenuState() = default;
