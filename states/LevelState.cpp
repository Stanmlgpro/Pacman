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
        } else if (e.key.code == sf::Keyboard::Up) {
            world->movePacman(UP);
        } else if (e.key.code == sf::Keyboard::Down) {
            world->movePacman(DOWN);
        } else if (e.key.code == sf::Keyboard::Left) {
            world->movePacman(LEFT);
        } else if (e.key.code == sf::Keyboard::Right) {
            world->movePacman(RIGHT);
        }
    }
}

void LevelState::Update() {
    if (world->Update()) {
        statemanager->PopState();
    }
}

void LevelState::Render(sf::RenderWindow& window) {
    world->Render();
}

LevelState::~LevelState() = default;