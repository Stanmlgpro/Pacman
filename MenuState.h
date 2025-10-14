//
// Created by stan on 10/14/25.
//

#ifndef PACMAN_MENUSTATE_H
#define PACMAN_MENUSTATE_H
#include "State.h"


class MenuState final : public State {
public:
    MenuState(std::shared_ptr<StateManager> statemanager);

    void HandleEvent(const sf::Event& e) override;
    void Update(float dt) override;
    void Render(sf::RenderWindow& window) override;

    ~MenuState() override;
private:
    std::shared_ptr<StateManager> statemanager;
};


#endif //PACMAN_MENUSTATE_H