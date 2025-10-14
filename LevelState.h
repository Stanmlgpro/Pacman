//
// Created by stan on 10/14/25.
//

#ifndef PACMAN_LEVELSTATE_H
#define PACMAN_LEVELSTATE_H
#include "State.h"

class LevelState final : public State {
public:
    LevelState(std::shared_ptr<StateManager> statemanager);

    void HandleEvent(const sf::Event& e) override;
    void Update(float dt) override;
    void Render(sf::RenderWindow& window) override;

    ~LevelState() override;
private:
    // std::unique_ptr<World> world;
    std::shared_ptr<StateManager> statemanager;
};

#endif //PACMAN_LEVELSTATE_H