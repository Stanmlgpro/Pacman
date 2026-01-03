//
// Created by stan on 10/14/25.
//

#ifndef PACMAN_MENUSTATE_H
#define PACMAN_MENUSTATE_H
#include "SFML/Graphics.hpp"
#include "State.h"
/**
 * @file MenuState.h
 * @brief MenuState Class
 */
namespace states {
struct ScoreEntry {
    std::string name;
    int score;
};
    /**
* @class MenuState
* @brief MenuState class Inherited from base State
*
* start screen in which the scores are displayed and the player can input their name
*/
class MenuState final : public State {

public:
    /**
* @brief Creates a LevelState object.
* @param statemanager Reference to the statemanager so we can pop and push states
*/
    MenuState(std::weak_ptr<StateManager> statemanager);
    /**
     * @brief Loads the highscores
     *
     * reads from the given file and displays those highscores onto the screen
     *
     * @param filename file to read
     * @return score per name
     */
    static std::vector<ScoreEntry> loadHighscores(const std::string& filename);
    /// Overrides State::HandleEvent
    void HandleEvent(const sf::Event& e) override;
    /// Overrides State::Update
    void Update() override;
    /// Overrides State::Render
    void Render(sf::RenderWindow& window) override;

    ~MenuState() override = default;

private:
    /** SFML utilities to show the state on the screen */
    std::string player;
    sf::Text title;
    sf::Font font;
    std::vector<ScoreEntry> highscores;
    sf::Text hsTitle;
    sf::Text hint;
};
} // namespace states

#endif // PACMAN_MENUSTATE_H