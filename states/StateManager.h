//
// Created by stan on 10/14/25.
//

#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H
#include <memory>
#include <stack>
/**
 * @file StateManager.h
 * @brief StateManager Class
 */
namespace sf {
class RenderWindow;
class Event;
} // namespace sf
namespace sounds {
class WorldSound;
}
namespace factory {
class EntityFactory;
}
namespace states {
class State;
/**
 * @enum StateID
 * @brief types of states
 */
enum StateID { MENU, LEVEL, PAUSED };
class Game;
class State;
/**
 * @class StateManager
 * @brief Manages a State stack
 *
 * updates the top state and renders/updates the top of its state stack
 */
class StateManager : public std::enable_shared_from_this<StateManager> {
public:
    /**
     * @brief Creates a StateManager object.
     * @param entity_factory Reference to the entity_factory so we can give it the states
     * @param world_sound Reference to the world_sounds so we can give it the states
     */
    StateManager(std::shared_ptr<factory::EntityFactory> entity_factory,
                 std::shared_ptr<sounds::WorldSound> world_sound);
    /**
     * @brief Handles to SFML view
     *
     * Calls the SFML event on the top of its state stack
     *
     * @param event called SFML event
     */
    void HandleEvent(const sf::Event& event);
    /**
     * @brief Push a new state onto the stack
     *
     * based on the stateid, push the correct state
     *
     * @param stateid type of state we want to push
     * @param player player to give to the state
     */
    void PushState(StateID stateid, std::string player);
    /**
     * @brief Pops states
     *
     * pops 'amount' amount of states from the stack
     *
     * @param amount amount of states to pop
     */
    void PopState(int amount);
    /**
     * @brief Updates states
     *
     * Updates the top State
     */
    void Update();
    /**
     * @brief Renders states
     *
     * Renders the top State
     */
    void Render(sf::RenderWindow& window);

    ~StateManager() = default;

private:
    std::stack<std::unique_ptr<State>> states{};
    std::shared_ptr<factory::EntityFactory> entity_factory;
    std::shared_ptr<sounds::WorldSound> world_sound;
};
} // namespace states

#endif // PACMAN_STATEMANAGER_H