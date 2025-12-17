//
// Created by stan on 10/14/25.
//

#include "PausedState.h"
#include "LevelState.h"
#include "MenuState.h"
#include "StateManager.h"

namespace states {
    PausedState::PausedState(std::shared_ptr<StateManager> statemanager) {
        this->statemanager = statemanager;

#ifdef _WIN32
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
#else
        font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
#endif

        title.setFont(font);
        title.setString("PAUSED");
        title.setCharacterSize(60);
        title.setFillColor(sf::Color::Yellow);
        title.setStyle(sf::Text::Bold);

        resumeHint.setFont(font);
        resumeHint.setString("Press ENTER to resume");
        resumeHint.setCharacterSize(30);
        resumeHint.setFillColor(sf::Color::White);

        menuHint.setFont(font);
        menuHint.setString("Press ESC to return to menu");
        menuHint.setCharacterSize(30);
        menuHint.setFillColor(sf::Color(180, 180, 180));
    }

    void PausedState::HandleEvent(const sf::Event& e) {
        if (e.type == sf::Event::KeyPressed) {
            if (e.key.code == sf::Keyboard::Escape) {
                std::cout << "Returning to menu..." << std::endl;
                statemanager->PopState(2); // remove pause
                std::cout << "Pops done" << std::endl;
            } else if (e.key.code == sf::Keyboard::Enter) {
                std::cout << "Resuming game..." << std::endl;
                statemanager->PopState(1);
            }
        }
    }

    void PausedState::Update() {}

    void PausedState::Render(sf::RenderWindow& window) {

        sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        window.draw(overlay);

        title.setPosition(window.getSize().x / 2.f - title.getGlobalBounds().width / 2.f, 100.f);
        resumeHint.setPosition(window.getSize().x / 2.f - resumeHint.getGlobalBounds().width / 2.f, 250.f);
        menuHint.setPosition(window.getSize().x / 2.f - menuHint.getGlobalBounds().width / 2.f, 310.f);

        window.draw(title);
        window.draw(resumeHint);
        window.draw(menuHint);
    }
}// namespace states