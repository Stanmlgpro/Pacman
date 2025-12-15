//
// Created by stan on 10/13/25.
//

#include "Game.h"

#include "factory/EntityFactory.h"
#include "factory/SFMLFactory.h"
#include "sounds/SFMLWorldSounds.h"
#include "states/MenuState.h"

Game::Game() : window(sf::VideoMode(750, 800), "Pac-Man") {
    camera = std::make_shared<Camera>(window.getSize().x, window.getSize().y);
    entity_factory = std::make_unique<factory::SFMLFactory>(window, "../Spritesheet.png", camera);
    world_sound = std::make_shared<sounds::SFMLWorldSounds>();
    state_manager = std::make_unique<states::StateManager>(entity_factory, world_sound);
    state_manager->PushState(states::MENU, "");
}

void Game::run() {
    while (window.isOpen()) {
        CheckInput();
        Update();
        Render();
    }
}

void Game::CheckInput() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::Resized) {
            auto size = window.getSize();

            // Update camera with new screen size
            camera->setScreenSize(static_cast<float>(size.x), static_cast<float>(size.y));

            // Create a new view matching the new window size
            sf::View view(sf::FloatRect(0.f, 0.f, static_cast<float>(size.x), static_cast<float>(size.y)));
            window.setView(view);
        }

        state_manager->HandleEvent(event);
    }
}

void Game::Update() const { state_manager->Update(); }

void Game::Render() {
    window.clear();
    state_manager->Render(window);
    window.display();
}

Game::~Game() = default;