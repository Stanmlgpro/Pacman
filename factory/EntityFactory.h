//
// Created by stan1 on 06/11/2025.
//

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H
#include "Camera.h"
#include "entities/ghost/Ghost.h"
#include <memory>
#include <vector>

namespace entities {
class Entity;
class Pacman;
} // namespace entities

namespace factory {
class EntityFactory {
public:
    virtual std::shared_ptr<entities::Wall> createWall(float x, float y) = 0;
    virtual std::shared_ptr<entities::Ghost> createGhost(float x, float y, std::shared_ptr<entities::Pacman>,
                                                         std::vector<std::vector<bool>> wallGrid, int id,
                                                         bool first_time) = 0;
    virtual std::shared_ptr<entities::Orb> createOrb(float x, float y) = 0;
    virtual std::shared_ptr<entities::PowerOrb> createPowerOrb(float x, float y) = 0;
    virtual std::shared_ptr<entities::Fruit> createFruit(float x, float y) = 0;
    virtual std::shared_ptr<entities::Pacman> createPacman(float speed, int mapwidth, int mapheight, float x,
                                                           float y) = 0;
    virtual std::unique_ptr<views::View> createWorldView() = 0;
    virtual std::shared_ptr<Camera> getCamera() = 0;
    virtual ~EntityFactory() = default;

protected:
    std::shared_ptr<Camera> camera;
};
} // namespace factory

#endif // ENTITYFACTORY_H
