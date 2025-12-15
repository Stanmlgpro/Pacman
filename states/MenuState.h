//
// Created by stan on 10/14/25.
//

#ifndef PACMAN_MENUSTATE_H
#define PACMAN_MENUSTATE_H
#include "SFML/Graphics.hpp"
#include "State.h"
namespace states {
struct ScoreEntry {
    std::string name;
    int score;
};

class MenuState final : public State {
public:
    MenuState(std::shared_ptr<StateManager> statemanager);

    static std::vector<ScoreEntry> loadHighscores(const std::string& filename);
    void HandleEvent(const sf::Event& e) override;
    void Update() override;
    void Render(sf::RenderWindow& window) override;

    ~MenuState() override;

private:
    std::shared_ptr<StateManager> statemanager;
    std::string player;
    sf::Text title;
    sf::Font font;
    std::vector<ScoreEntry> highscores;
    sf::Text hsTitle;
    sf::Text hint;
};
} // namespace states

#endif // PACMAN_MENUSTATE_H