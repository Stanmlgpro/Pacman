//
// Created by stan1 on 06/11/2025.
//

#include "SFMLFactory.h"
#include "entities/Wall.h"
#include "entities/ghost/Ghost.h"
#include "entities/Orb.h"
#include "entities/Pacman.h"
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

std::shared_ptr<Entity> SFMLFactory::createWall(float x, float y) {
    auto wall = std::make_shared<Wall>(x, y);
    wall->setView(std::make_unique<SFMLWallView>(texture, wall, window, camera));
    return wall;
}
std::shared_ptr<Entity> SFMLFactory::createOrb(float x, float y) {
    auto orb = std::make_shared<Orb>(x, y, false);
    orb->setView(std::make_unique<SFMLOrbView>(texture, orb, window, camera));
    return orb;
}
std::shared_ptr<Entity> SFMLFactory::createBigOrb(float x, float y) {
    auto orb = std::make_shared<Orb>(x, y, true);
    orb->setView(std::make_unique<SFMLOrbView>(texture, orb, window, camera));
    return orb;
}
std::shared_ptr<Entity> SFMLFactory::createGhost(float x, float y, std::shared_ptr<Pacman> pacman, std::vector<std::vector<bool>> wallGrid, int id) {
    auto ghost = std::make_shared<Ghost>(x, y, pacman, wallGrid, id);
    switch (id) {
    case 0:
        ghost->setView(std::make_unique<SFMLLockedGhostView>(texture, ghost, window, camera));
        break;
    case 1:
        ghost->setView(std::make_unique<SFMLChaseGhostView>(texture, ghost, window, camera));
        break;
    case 2:
        ghost->setView(std::make_unique<SFMLPredictGhost1View>(texture, ghost, window, camera));
        break;
    case 3:
        ghost->setView(std::make_unique<SFMLPredictGhost2View>(texture, ghost, window, camera));
        break;
    }
    return ghost;
}
std::shared_ptr<Pacman> SFMLFactory::createPacman(float speed, int mapwidth, int mapheight, float x, float y) {
    auto pacman = std::make_shared<Pacman>(speed, mapwidth, mapheight, x, y);
    pacman->setView(std::make_unique<SFMLPacmanView>(texture, pacman, window, camera));
    return pacman;
}

std::shared_ptr<Camera> SFMLFactory::getCamera() {
    return camera;
}
