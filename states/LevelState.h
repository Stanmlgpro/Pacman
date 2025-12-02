//
// Created by stan on 10/14/25.
//

#ifndef PACMAN_LEVELSTATE_H
#define PACMAN_LEVELSTATE_H
#include "State.h"
#include "World.h"

namespace factory {
    class EntityFactory;
}

class LevelState final : public State {
public:
    LevelState(std::shared_ptr<StateManager> statemanager, std::shared_ptr<factory::EntityFactory> entity_factory, std::shared_ptr<WorldSound> world_sounds, std::string player);

    void Resize(unsigned int width, unsigned int height);
    void HandleEvent(const sf::Event& e) override;
    void Update() override;
    void Render(sf::RenderWindow& window) override;

    ~LevelState() override;
private:
    std::unique_ptr<World> world;
    std::shared_ptr<StateManager> statemanager;
    std::shared_ptr<factory::EntityFactory> entity_factory;
    std::shared_ptr<WorldSound> world_sounds;
    std::string player;
    sf::Font font;
    sf::Text scoreText;
    sf::Text livesText;
};

#endif //PACMAN_LEVELSTATE_H