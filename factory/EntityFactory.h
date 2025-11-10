//
// Created by stan1 on 06/11/2025.
//

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H
#include <memory>
#include <vector>
#include "Camera.h"
#include "entities/ghost/Ghost.h"

class Entity;
class Pacman;
class EntityFactory {
public:
    virtual std::shared_ptr<Wall> createWall(float x, float y) = 0;
    virtual std::shared_ptr<Ghost> createGhost(float x, float y, std::shared_ptr<Pacman>, std::vector<std::vector<bool>> wallGrid, int id, bool first_time) = 0;
    virtual std::shared_ptr<Orb> createOrb(float x, float y) = 0;
    virtual std::shared_ptr<Orb> createBigOrb(float x, float y) = 0;
    virtual std::shared_ptr<Pacman> createPacman(float speed, int mapwidth, int mapheight, float x, float y) = 0;
    virtual std::shared_ptr<Camera> getCamera() = 0;
    virtual ~EntityFactory() = default;
protected:
    std::shared_ptr<Camera> camera;
};

#endif //ENTITYFACTORY_H
