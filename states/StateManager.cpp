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
#include <utility>

namespace states {
StateManager::StateManager(std::shared_ptr<factory::EntityFactory> entity_factory,
                           std::shared_ptr<sounds::WorldSound> world_sound) {
    // initiate variables
    this->entity_factory = std::move(entity_factory);
    this->world_sound = std::move(world_sound);
}

void StateManager::PushState(const StateID stateid, std::string player) {
    // push the correct states based on the StateID
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
    // check for incorrect formatting
    if (!state)
        return;
    // std::move since we create a unique_ptr here to push onto our state stack
    states.push(std::move(state));
}

void StateManager::PopState(const int amount) {
    // pop "amount" amount of states
    for (int i = 0; i < amount; i++) {
        if (!states.empty())
            states.pop();
        std::cout << states.size() << std::endl;
    }
}

void StateManager::HandleEvent(const sf::Event& event) {
    // propagate the event through the stack top
    if (!states.empty()) {
        states.top()->HandleEvent(event);
    }
}

void StateManager::Update() {
    // propagate the update call through the stack top
    if (!states.empty())
        states.top()->Update();
}

void StateManager::Render(sf::RenderWindow& window) {
    // propagate the render call through the stack top
    if (!states.empty())
        states.top()->Render(window);
}

} // namespace states