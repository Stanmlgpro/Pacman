//
// Created by stan on 10/14/25.
//

#include "StateManager.h"
#include "LevelState.h"
#include "MenuState.h"
#include "PausedState.h"
#include "State.h"
#include "sounds/WorldSound.h"
#include <SFML/Graphics.hpp>

namespace states {
StateManager::StateManager(std::shared_ptr<factory::EntityFactory> entity_factory,
                           std::shared_ptr<sounds::WorldSound> world_sound) {
    this->entity_factory = entity_factory;
    this->world_sound = world_sound;
}

void StateManager::PushState(StateID stateid, std::string player) {
    std::unique_ptr<State> state;
    if (stateid == StateID::MENU) {
        state = std::make_unique<MenuState>(shared_from_this());
    }
    if (stateid == StateID::LEVEL) {
        state = std::make_unique<LevelState>(shared_from_this(), entity_factory, world_sound, player);
    }
    if (stateid == StateID::PAUSED) {
        state = std::make_unique<PausedState>(shared_from_this());
    }
    if (!state)
        return;
    states.push(std::move(state));
}

void StateManager::PopState() {
    if (!states.empty())
        states.pop();
    std::cout << states.size() << std::endl;
}

void StateManager::HandleEvent(const sf::Event& event) {
    if (!states.empty()) {
        states.top()->HandleEvent(event);
    }
}

void StateManager::Update() {
    if (!states.empty())
        states.top()->Update();
}

void StateManager::Render(sf::RenderWindow& window) {
    if (!states.empty())
        states.top()->Render(window);
}
} // namespace states