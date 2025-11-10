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
    if (e.type == sf::Event::TextEntered) {
        char c = static_cast<char>(e.text.unicode);
        if (e.text.unicode == 8) {
            if (!player.empty()) player.pop_back();
        }
        else if ((std::isalnum(c) || c == '_' || c == '-') && player.size() < 16) {
            player += c;
        }
    }
    else if (e.type == sf::Event::KeyPressed) {
        if (e.key.code == sf::Keyboard::Enter) {
            std::cout << "Starting new level with player: " << player << std::endl;
            statemanager->PushState(LEVEL, (player != "") ? player : "Unknown");
        }
    }
}

void MenuState::Update() {}

void MenuState::Render(sf::RenderWindow& window) {
}

MenuState::~MenuState() = default;
