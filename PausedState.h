//
// Created by stan on 10/14/25.
//

#ifndef PACMAN_PAUSEDSTATE_H
#define PACMAN_PAUSEDSTATE_H
#include "State.h"

class PausedState final : public State {
public:
    PausedState(std::shared_ptr<StateManager> statemanager);

    void HandleEvent(const sf::Event& e) override;
    void Update(float dt) override;
    void Render(sf::RenderWindow& window) override;

    ~PausedState() override;
private:
    // std::unique_ptr<World> world;
    std::shared_ptr<StateManager> statemanager;
};


#endif //PACMAN_PAUSEDSTATE_H