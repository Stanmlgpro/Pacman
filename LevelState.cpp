//
// Created by stan on 10/14/25.
//

#include "LevelState.h"
#include "PausedState.h"
#include "StateManager.h"
#include "World.h"

LevelState::LevelState(std::shared_ptr<StateManager> statemanager, std::shared_ptr<EntityFactory> entity_factory) {
    this->statemanager = statemanager;
    this->entity_factory = entity_factory;
    this->world = std::make_unique<World>("../map.txt", entity_factory);
    std::cout << "new level and world created" << std::endl;
}

void LevelState::HandleEvent(const sf::Event &e) {
    if (e.type == sf::Event::KeyPressed) {
        if (e.key.code == sf::Keyboard::Escape) {
            statemanager->PushState(PAUSED);
        }
        else {
            std::cout << e.key.code << std::endl;
            std::cout << "pressed while playing the game" << std::endl;
        }
    }
}

void LevelState::Update(float dt) {
    world->Update(dt);
}

void LevelState::Render(sf::RenderWindow& window) {
    world->Render();
}

LevelState::~LevelState() = default;