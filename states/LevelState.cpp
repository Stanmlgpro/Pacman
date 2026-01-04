//
// Created by stan on 10/14/25.
//

#include "LevelState.h"

#include <views/SFMLWorldView.h>

#include <utility>

#include "PausedState.h"
#include "StateManager.h"
#include "World.h"
namespace states {
LevelState::LevelState(std::weak_ptr<StateManager> statemanager, std::shared_ptr<factory::EntityFactory> entity_factory,
                       std::shared_ptr<sounds::WorldSound> world_sounds, const std::string& player)
    :   State(std::move(statemanager)),
        entity_factory(std::move(entity_factory)),
        world_sounds(std::move(world_sounds)),
        player(player) {
    // initiate variables

    // load the world based on a txt file
    this->world = std::make_unique<World>("../map.txt", this->entity_factory, this->world_sounds, player);
    // start sound
    this->world_sounds->Start();
    std::cout << "new level and world created" << std::endl;
}

void LevelState::HandleEvent(const sf::Event& e) {
    // propagate events through the World
    // or simply pop a paused state on Escape
    if (e.type == sf::Event::KeyPressed) {
        if (e.key.code == sf::Keyboard::Escape) {
            statemanager.lock()->PushState(PAUSED, "");
        } else if (e.key.code == sf::Keyboard::Up) {
            world->movePacman(UP);
        } else if (e.key.code == sf::Keyboard::Down) {
            world->movePacman(DOWN);
        } else if (e.key.code == sf::Keyboard::Left) {
            world->movePacman(LEFT);
        } else if (e.key.code == sf::Keyboard::Right) {
            world->movePacman(RIGHT);
        }
    }
}

void LevelState::Update() {
    // propagate the update function
    if (world->Update()) {
        statemanager.lock()->PopState(1);
    }
}
// propagate the render function
void LevelState::Render(sf::RenderWindow& window) { world->Render(); }
} // namespace states