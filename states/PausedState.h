//
// Created by stan on 10/14/25.
//

#ifndef PACMAN_PAUSEDSTATE_H
#define PACMAN_PAUSEDSTATE_H
#include "SFML/Graphics.hpp"
#include "State.h"
/**
 * @file PausedState.h
 * @brief PausedState Class
 */
namespace states {
/**
 * @class PausedState
 * @brief PausedState class Inherited from base State
 *
 * pushed when the user wants to pause the game and popped on resume
 */
class PausedState final : public State {
public:
    /**
     * @brief Creates a PausedState object.
     * @param statemanager Reference to the statemanager so we can pop and push states
     */
    explicit PausedState(std::weak_ptr<StateManager> statemanager);

    /// Overrides State::HandleEvent
    void HandleEvent(const sf::Event& e) override;
    /// Overrides State::HandleEvent
    void Update() override;
    /// Overrides State::HandleEvent
    void Render(sf::RenderWindow& window) override;

    ~PausedState() override = default;

private:
    /** SFML utilities to show the state on the screen */
    sf::Text title;
    sf::Font font;
    sf::Text resumeHint;
    sf::Text menuHint;
};
} // namespace states

#endif // PACMAN_PAUSEDSTATE_H