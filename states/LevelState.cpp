//
// Created by stan on 10/14/25.
//

#include "LevelState.h"

#include <views/SFMLWorldView.h>

#include "PausedState.h"
#include "StateManager.h"
#include "World.h"
namespace states {
LevelState::LevelState(std::weak_ptr<StateManager> statemanager, std::shared_ptr<factory::EntityFactory> entity_factory,
                       std::shared_ptr<sounds::WorldSound> world_sounds, std::string player)
    : player(player) {
    this->statemanager = statemanager;
    this->entity_factory = entity_factory;
    this->world_sounds = world_sounds;

    this->world = std::make_unique<World>("../map2.txt", entity_factory, world_sounds, player);
    world_sounds->Start();
    std::cout << "new level and world created" << std::endl;
}

void LevelState::HandleEvent(const sf::Event& e) {
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
    if (world->Update()) {
        statemanager.lock()->PopState(1);
    }
}

void LevelState::Render(sf::RenderWindow& window) { world->Render(); }
} // namespace states