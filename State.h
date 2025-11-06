//
// Created by stan on 10/14/25.
//

#ifndef PACMAN_STATE_H
#define PACMAN_STATE_H
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

class StateManager;

class State {
public:
    explicit State() = default;

    virtual void HandleEvent(const sf::Event& e) = 0;
    virtual void Update() = 0;
    virtual void Render(sf::RenderWindow& window) = 0;

    virtual ~State() = default;
private:
    std::shared_ptr<StateManager> statemanager;
};


#endif //PACMAN_STATE_H