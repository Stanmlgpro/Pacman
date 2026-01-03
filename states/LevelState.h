//
// Created by stan on 10/14/25.
//

#ifndef PACMAN_LEVELSTATE_H
#define PACMAN_LEVELSTATE_H
#include "State.h"
#include "World.h"
/**
 * @file LevelState.h
 * @brief LevelState Class
 */
namespace factory {
class EntityFactory;
}

namespace states {
    /**
* @class LevelState
* @brief LevelState class Inherited from base State
*
* orchestrates the world and gives it all the inputs from the user
*/
class LevelState final : public State {
public:
    /**
* @brief Creates a LevelState object.
* @param statemanager Reference to the statemanager so we can pop and push states
* @param entity_factory Reference to the entity_factory so we can give it the world
* @param world_sounds Reference to the world_sounds so we can give it the world
* @param player Reference to the player so we can give it the world's score
*/
    LevelState(std::weak_ptr<StateManager> statemanager, std::shared_ptr<factory::EntityFactory> entity_factory,
               std::shared_ptr<sounds::WorldSound> world_sounds, std::string player);

    /// Overrides State::HandleEvent
    void HandleEvent(const sf::Event& e) override;
    /// Overrides State::Update
    void Update() override;
    /// Overrides State::Render
    void Render(sf::RenderWindow& window) override;

    ~LevelState() override = default;

private:
    std::unique_ptr<World> world;
    std::shared_ptr<factory::EntityFactory> entity_factory;
    std::shared_ptr<sounds::WorldSound> world_sounds;
    std::string player;
};
} // namespace states
#endif // PACMAN_LEVELSTATE_H