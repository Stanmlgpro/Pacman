//
// Created by stan on 10/13/25.
//

#include "Game.h"

#include "factory/EntityFactory.h"
#include "factory/SFMLFactory.h"
#include "sounds/SFMLWorldSounds.h"
#include "states/MenuState.h"

Game::Game() : window(sf::VideoMode(750, 800), "Pac-Man") {
    // create all needed variables to give to the statemanager
    camera = std::make_shared<Camera>();
    camera->setScreenSize(window.getSize().x, window.getSize().y);
    entity_factory = std::make_unique<factory::SFMLFactory>(window, "../Spritesheet.png", camera);
    world_sound = std::make_shared<sounds::SFMLWorldSounds>();
    state_manager = std::make_unique<states::StateManager>(entity_factory, world_sound);
    // push the beginning menu state
    state_manager->PushState(states::MENU, "");
}

void Game::run() {
    // run the main game loop
    while (window.isOpen()) {
        // check for input then update, then render
        CheckInput();
        Update();
        Render();
    }
}

void Game::CheckInput() {
    // check for an SFML event
    sf::Event event{};
    while (window.pollEvent(event)) {
        // on closing, close the window
        if (event.type == sf::Event::Closed)
            window.close();

        // on resizing
        if (event.type == sf::Event::Resized) {
            // set the new size
            auto size = window.getSize();

            // Update camera with new screen size
            camera->setScreenSize(static_cast<float>(size.x), static_cast<float>(size.y));

            // Create a new view matching the new window size
            sf::View view(sf::FloatRect(0.f, 0.f, static_cast<float>(size.x), static_cast<float>(size.y)));
            window.setView(view);
        }

        // let state_manager handle the events after
        state_manager->HandleEvent(event);
    }
}

void Game::Update() const { state_manager->Update(); } // propagate the update through the state manager

void Game::Render() {
    // on rendering clear the window
    window.clear();
    state_manager->Render(window); // then draw everything
    window.display(); // then display everything on the screen
}