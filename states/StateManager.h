//
// Created by stan on 10/14/25.
//

#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H
#include <memory>
#include <stack>

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
enum StateID { MENU, LEVEL, PAUSED };
class Game;
class State;
class StateManager : public std::enable_shared_from_this<StateManager> {
public:
    StateManager(std::shared_ptr<factory::EntityFactory> entity_factory,
                 std::shared_ptr<sounds::WorldSound> world_sound);

    void HandleEvent(const sf::Event& event);

    void PushState(StateID stateid, std::string player);
    void PopState(int amount);

    void Update();

    void Render(sf::RenderWindow& window);

    ~StateManager() = default;
private:
    std::stack<std::unique_ptr<State>> states{};
    std::shared_ptr<factory::EntityFactory> entity_factory;
    std::shared_ptr<sounds::WorldSound> world_sound;
};
} // namespace states

#endif // PACMAN_STATEMANAGER_H