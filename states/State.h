//
// Created by stan on 10/14/25.
//

#ifndef PACMAN_STATE_H
#define PACMAN_STATE_H
#include <iostream>
#include <memory>
/**
 * @file State.h
 * @brief State Class
 */
namespace sf {
class RenderWindow;
class Event;
} // namespace sf
namespace states {
class StateManager;
/**
 * @class State
 * @brief Main state class
 *
 * Parent State class to add al basic behaviour of states
 */
class State {
public:
    /**
     * @brief Creates a State object.
     */
    explicit State() = default;
    /**
     * @brief Handles SFML events
     *
     * overwritten by all child classes
     * implements the SFML event given by the user and processes it
     *
     * @param e event given
     */
    virtual void HandleEvent(const sf::Event& e) = 0;
    /**
     * @brief Updates the State
     *
     * overwritten by all child classes
     * called every frame to ensure correct visuals and propagated through all variables of the states that need it
     */
    virtual void Update() = 0;
    /**
     * @brief Renders states
     *
     * overwritten by all child classes
     * called every frame to visually update all the states and propagated through all variables of the states that need
     * to be visualised
     *
     * @window window on which to draw
     */
    virtual void Render(sf::RenderWindow& window) = 0;

    virtual ~State() = default;

protected:
    std::weak_ptr<StateManager> statemanager;
};
} // namespace states

#endif // PACMAN_STATE_H