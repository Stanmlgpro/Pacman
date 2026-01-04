//
// Created by stan1 on 06/11/2025.
//

#include "SFMLFactory.h"

#include "SpriteAtlas.h"
#include "entities/Pacman.h"
#include "entities/Wall.h"
#include "entities/collectable/Fruit.h"
#include "entities/collectable/Orb.h"
#include "entities/collectable/PowerOrb.h"
#include "entities/ghost/ChaseGhost.h"
#include "entities/ghost/Ghost.h"
#include "entities/ghost/LockedGhost.h"
#include "entities/ghost/PredictGhost.h"
#include "views/SFMLPacmanView.h"
#include "views/SFMLWallView.h"
#include "views/SFMLWorldView.h"
#include "views/collectableview/SFMLFruitView.h"
#include "views/collectableview/SFMLOrbView.h"
#include "views/collectableview/SFMLPowerOrbView.h"
#include "views/ghostview/SFMLChaseGhostView.h"
#include "views/ghostview/SFMLLockedGhostView.h"
#include "views/ghostview/SFMLPredictGhost1View.h"
#include "views/ghostview/SFMLPredictGhost2View.h"

#include <iostream>
#include <utility>
namespace factory {
SFMLFactory::SFMLFactory(sf::RenderWindow& window, const std::string& texture_input, std::shared_ptr<Camera> camera)
    : window(window) {
    // assign all variables
    this->camera = std::move(camera);
    if (!texture.loadFromFile(texture_input))
        throw std::runtime_error("Failed to load textures: " + texture_input);
    // create a new atlas with the texture file
    this->atlas = std::make_shared<sprites::SpriteAtlas>(texture);
}
// create the entities and attach the Views
std::shared_ptr<entities::Wall> SFMLFactory::createWall(float x, float y) {
    auto wall = std::make_shared<entities::Wall>(x, y);
    wall->setView(std::make_unique<views::SFMLWallView>(texture, atlas, wall, window, camera));
    return wall;
}
std::shared_ptr<entities::Orb> SFMLFactory::createOrb(float x, float y) {
    auto orb = std::make_shared<entities::Orb>(x, y);
    orb->setView(std::make_unique<views::SFMLOrbView>(texture, atlas, orb, window, camera));
    return orb;
}
std::shared_ptr<entities::PowerOrb> SFMLFactory::createPowerOrb(float x, float y) {
    auto powerorb = std::make_shared<entities::PowerOrb>(x, y);
    powerorb->setView(std::make_unique<views::SFMLPowerOrbView>(texture, atlas, powerorb, window, camera));
    return powerorb;
}
std::shared_ptr<entities::Fruit> SFMLFactory::createFruit(float x, float y) {
    // Choose 1 of 7 random possible fruits
    const int rand_num = singleton::Random::getInstance().get(0, 7);
    switch (rand_num) {
    case 0: {
        auto fruit = std::make_shared<entities::Cherry>(x, y);
        fruit->setView(std::make_unique<views::SFMLCherryView>(texture, atlas, fruit, window, camera));
        return fruit;
    }
    case 1: {
        auto fruit = std::make_shared<entities::Strawberry>(x, y);
        fruit->setView(std::make_unique<views::SFMLStrawberryView>(texture, atlas, fruit, window, camera));
        return fruit;
    }
    case 2: {
        auto fruit = std::make_shared<entities::Orange>(x, y);
        fruit->setView(std::make_unique<views::SFMLOrangeView>(texture, atlas, fruit, window, camera));
        return fruit;
    }
    case 3: {
        auto fruit = std::make_shared<entities::Apple>(x, y);
        fruit->setView(std::make_unique<views::SFMLAppleView>(texture, atlas, fruit, window, camera));
        return fruit;
    }
    case 4: {
        auto fruit = std::make_shared<entities::Melon>(x, y);
        fruit->setView(std::make_unique<views::SFMLMelonView>(texture, atlas, fruit, window, camera));
        return fruit;
    }
    case 5: {
        auto fruit = std::make_shared<entities::Galaxian>(x, y);
        fruit->setView(std::make_unique<views::SFMLGalaxianView>(texture, atlas, fruit, window, camera));
        return fruit;
    }
    case 6: {
        auto fruit = std::make_shared<entities::Bell>(x, y);
        fruit->setView(std::make_unique<views::SFMLBellView>(texture, atlas, fruit, window, camera));
        return fruit;
    }
    case 7: {
        auto fruit = std::make_shared<entities::Key>(x, y);
        fruit->setView(std::make_unique<views::SFMLKeyView>(texture, atlas, fruit, window, camera));
        return fruit;
    }
    default:
        return nullptr;
    }
}
std::shared_ptr<entities::Ghost> SFMLFactory::createGhost(float x, float y, std::shared_ptr<entities::Pacman> pacman,
                                                          std::vector<std::vector<bool>> wallGrid, int id,
                                                          const bool first_time) {
    std::shared_ptr<entities::Ghost> ghost;
    // choose chase time and ghost type based on id
    switch (id) {
    case 0:
        ghost = std::make_shared<entities::LockedGhost>(x, y, pacman, wallGrid, id, 0.f);
        ghost->setView(std::make_unique<views::SFMLLockedGhostView>(texture, atlas, ghost, window, camera));
        break;
    case 1:
        ghost = std::make_shared<entities::ChaseGhost>(x, y, pacman, wallGrid, id, 0.f);
        ghost->setView(std::make_unique<views::SFMLChaseGhostView>(texture, atlas, ghost, window, camera));
        break;
    case 2:
        ghost = std::make_shared<entities::PredictGhost>(x, y, pacman, wallGrid, id, first_time ? 5.f : 0.f);
        ghost->setView(std::make_unique<views::SFMLPredictGhost1View>(texture, atlas, ghost, window, camera));
        break;
    case 3:
        ghost = std::make_shared<entities::PredictGhost>(x, y, pacman, wallGrid, id, first_time ? 10.f : 0.f);
        ghost->setView(std::make_unique<views::SFMLPredictGhost2View>(texture, atlas, ghost, window, camera));
        break;
    default: ;
    }
    return ghost;
}
std::shared_ptr<entities::Pacman> SFMLFactory::createPacman(float speed, int mapwidth, int mapheight, float x,
                                                            float y) {
    auto pacman = std::make_shared<entities::Pacman>(speed, mapwidth, mapheight, x, y);
    pacman->setView(std::make_unique<views::SFMLPacmanView>(texture, atlas, pacman, window, camera));
    return pacman;
}
// create the worldview
std::unique_ptr<views::View> SFMLFactory::createWorldView() {
    return std::make_unique<views::SFMLWorldView>(texture, atlas, window, camera);
}
// simple getter
std::shared_ptr<Camera> SFMLFactory::getCamera() { return camera; }
} // namespace factory