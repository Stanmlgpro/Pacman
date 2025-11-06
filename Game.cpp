//
// Created by stan on 10/13/25.
//

#include "Game.h"

#include "EntityFactory.h"
#include "SFMLFactory.h"
#include "MenuState.h"

Game::Game() : window(sf::VideoMode(800, 600), "Pac-Man") {
    entity_factory = std::make_unique<SFMLFactory>(window, "../pacman.png");
    state_manager = std::make_unique<StateManager>(entity_factory);
    state_manager->PushState(MENU);
}

void Game::run() {
    while (window.isOpen()) {
        const float dt = time.restart().asSeconds();

        CheckInput();
        Update(dt);
        Render();
    }
}

void Game::CheckInput() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        state_manager->HandleEvent(event);
    }
}

void Game::Update(const float dt) const {
    state_manager->Update(dt);
}

void Game::Render() {
    window.clear();
    state_manager->Render(window);
    window.display();
}

Game::~Game() = default;