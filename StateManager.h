//
// Created by stan on 10/14/25.
//

#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H
#include <memory>
#include <stack>
#include <SFML/Graphics.hpp>
#include "State.h"

class State;
class StateManager {
public:
    StateManager() = default;

    void HandleEvent(const sf::Event& event);

    void PushState(std::unique_ptr<State> state);
    void PopState();

    void Update(float dt);

    void Render(sf::RenderWindow& window);

    ~StateManager() = default;
private:
    std::stack<std::unique_ptr<State>> states{};
};


#endif //PACMAN_STATEMANAGER_H