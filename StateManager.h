//
// Created by stan on 10/14/25.
//

#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H
#include <memory>
#include <stack>
#include <SFML/Graphics.hpp>
#include "State.h"


class EntityFactory;

enum StateID {
    MENU,
    LEVEL,
    PAUSED
};
class Game;
class State;
class StateManager : public std::enable_shared_from_this<StateManager> {
public:
    StateManager(std::shared_ptr<EntityFactory> entity_factory);

    void HandleEvent(const sf::Event& event);

    void PushState(StateID stateid);
    void PopState();

    void Update(float dt);

    void Render(sf::RenderWindow& window);

    ~StateManager() = default;
private:
    std::stack<std::unique_ptr<State>> states{};
    std::shared_ptr<EntityFactory> entity_factory;
};


#endif //PACMAN_STATEMANAGER_H