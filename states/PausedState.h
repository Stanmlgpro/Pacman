//
// Created by stan on 10/14/25.
//

#ifndef PACMAN_PAUSEDSTATE_H
#define PACMAN_PAUSEDSTATE_H
#include "SFML/Graphics.hpp"
#include "State.h"
namespace states {
class PausedState final : public State {
public:
    PausedState(std::shared_ptr<StateManager> statemanager);

    void HandleEvent(const sf::Event& e) override;
    void Update() override;
    void Render(sf::RenderWindow& window) override;

    ~PausedState() override = default;

private:
    std::shared_ptr<StateManager> statemanager;
    sf::Text title;
    sf::Font font;
    sf::Text resumeHint;
    sf::Text menuHint;
};
} // namespace states

#endif // PACMAN_PAUSEDSTATE_H