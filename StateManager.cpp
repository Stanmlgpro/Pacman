//
// Created by stan on 10/14/25.
//

#include "StateManager.h"
#include "State.h"

void StateManager::PushState(std::unique_ptr<State> state) {
    if (!state) return;
    states.push(std::move(state));
}

void StateManager::PopState() {
    if (!states.empty()) states.pop();
}

void StateManager::HandleEvent(const sf::Event& event) {
    if (!states.empty()) {
        states.top()->HandleEvent(event);
    }
}

void StateManager::Update(const float dt) {
    if (!states.empty()) states.top()->Update(dt);
}

void StateManager::Render(sf::RenderWindow& window) {
    if (!states.empty()) states.top()->Render(window);
}