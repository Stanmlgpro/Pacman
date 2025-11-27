//
// Created by stan1 on 06/11/2025.
//

#include "SFMLFactory.h"
#include "entities/Wall.h"
#include "entities/ghost/Ghost.h"
#include "entities/Orb.h"
#include "entities/Pacman.h"
#include "entities/ghost/ChaseGhost.h"
#include "entities/ghost/LockedGhost.h"
#include "entities/ghost/PredictGhost.h"
#include "views/SFMLWallView.h"
#include "views/SFMLPacmanView.h"
#include "views/SFMLOrbView.h"
#include "views/ghostview/SFMLLockedGhostView.h"
#include "views/ghostview/SFMLChaseGhostView.h"
#include "views/ghostview/SFMLPredictGhost1View.h"
#include "views/ghostview/SFMLPredictGhost2View.h"

SFMLFactory::SFMLFactory(sf::RenderWindow& window, std::string texture_input, std::shared_ptr<Camera> camera) : window(window) {
    this->camera = camera;
    if (!texture.loadFromFile(texture_input))
        throw std::runtime_error("Failed to load textures: " + texture_input);
}

std::shared_ptr<entities::Wall> SFMLFactory::createWall(float x, float y) {
    auto wall = std::make_shared<entities::Wall>(x, y);
    wall->setView(std::make_unique<SFMLWallView>(texture, wall, window, camera));
    return wall;
}
std::shared_ptr<entities::Orb> SFMLFactory::createOrb(float x, float y) {
    auto orb = std::make_shared<entities::Orb>(x, y, false);
    orb->setView(std::make_unique<SFMLOrbView>(texture, orb, window, camera));
    return orb;
}
std::shared_ptr<entities::Orb> SFMLFactory::createBigOrb(float x, float y) {
    auto orb = std::make_shared<entities::Orb>(x, y, true);
    orb->setView(std::make_unique<SFMLOrbView>(texture, orb, window, camera));
    return orb;
}
std::shared_ptr<entities::Ghost> SFMLFactory::createGhost(float x, float y, std::shared_ptr<entities::Pacman> pacman, std::vector<std::vector<bool>> wallGrid, int id, bool first_time) {
    std::shared_ptr<entities::Ghost> ghost;
    switch (id) {
    case 0:
        ghost = std::make_shared<entities::LockedGhost>(x, y, pacman, wallGrid, id, 0.f);
        ghost->setView(std::make_unique<SFMLLockedGhostView>(texture, ghost, window, camera));
        break;
    case 1:
        ghost = std::make_shared<entities::ChaseGhost>(x, y, pacman, wallGrid, id, 0.f);
        ghost->setView(std::make_unique<SFMLChaseGhostView>(texture, ghost, window, camera));
        break;
    case 2:
        ghost = std::make_shared<entities::PredictGhost>(x, y, pacman, wallGrid, id, first_time ? 5.f : 0.f);
        ghost->setView(std::make_unique<SFMLPredictGhost1View>(texture, ghost, window, camera));
        break;
    case 3:
        ghost = std::make_shared<entities::PredictGhost>(x, y, pacman, wallGrid, id, first_time ? 10.f : 0.f);
        ghost->setView(std::make_unique<SFMLPredictGhost2View>(texture, ghost, window, camera));
        break;
    }
    return ghost;
}
std::shared_ptr<entities::Pacman> SFMLFactory::createPacman(float speed, int mapwidth, int mapheight, float x, float y) {
    auto pacman = std::make_shared<entities::Pacman>(speed, mapwidth, mapheight, x, y);
    pacman->setView(std::make_unique<SFMLPacmanView>(texture, pacman, window, camera));
    return pacman;
}

std::shared_ptr<Camera> SFMLFactory::getCamera() {
    return camera;
}
