//
// Created by stan on 10/13/25.
//

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H
#include "sounds/WorldSound.h"
#include "states/State.h"
#include "states/StateManager.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Camera;
namespace factory {
class EntityFactory;
}

class Game {
public:
    Game();

    void run();

    ~Game() = default;
private:
    void Update() const;
    void Render();
    void CheckInput();

    std::shared_ptr<states::StateManager> state_manager;
    sf::RenderWindow window;
    sf::Clock time;

    std::shared_ptr<factory::EntityFactory> entity_factory;
    std::shared_ptr<Camera> camera;

    std::shared_ptr<sounds::WorldSound> world_sound;
};

#endif // PACMAN_GAME_H