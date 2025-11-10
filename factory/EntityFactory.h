//
// Created by stan1 on 06/11/2025.
//

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H
#include <memory>
#include <vector>
#include "Camera.h"

class Entity;
class Pacman;
class EntityFactory {
public:
    virtual std::shared_ptr<Entity> createWall(float x, float y) = 0;
    virtual std::shared_ptr<Entity> createGhost(float x, float y, std::shared_ptr<Pacman>, std::vector<std::vector<bool>> wallGrid, int id, bool first_time) = 0;
    virtual std::shared_ptr<Entity> createOrb(float x, float y) = 0;
    virtual std::shared_ptr<Entity> createBigOrb(float x, float y) = 0;
    virtual std::shared_ptr<Pacman> createPacman(float speed, int mapwidth, int mapheight, float x, float y) = 0;
    virtual std::shared_ptr<Camera> getCamera() = 0;
    virtual ~EntityFactory() = default;
protected:
    std::shared_ptr<Camera> camera;
};

#endif //ENTITYFACTORY_H
