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
/**
 * @file Game.h
 * @brief Game Class
 */
class Camera;
namespace factory {
class EntityFactory;
}
/**
 * @class Game
 * @brief Main class that sets up the system
 */
class Game {
public:
    /**
     * @brief Creates a Game object.
     */
    Game();
    /**
     * @brief runs the game loop
     *
     * checks for SFML events and updates then renders the state_manager
     */
    void run();

    ~Game() = default;

private:
    /**
     *@brief updates the state_manager
     */
    void Update() const;
    /**
     *@brief renders the state_manager
     */
    void Render();
    /**
     * @brief checks for SFML event
     */
    void CheckInput();

    std::shared_ptr<states::StateManager> state_manager;
    sf::RenderWindow window;

    std::shared_ptr<factory::EntityFactory> entity_factory;
    std::shared_ptr<Camera> camera;

    std::shared_ptr<sounds::WorldSound> world_sound;
};

#endif // PACMAN_GAME_H