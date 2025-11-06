//
// Created by stan1 on 14/10/2025.
//

#ifndef WORLD_H
#define WORLD_H
#include <memory>
#include <string>
#include "Entity.h"

class EntityFactory;
enum class my_enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class World {
public:
    explicit World(std::string filename, std::shared_ptr<EntityFactory> entity_factory);

    void MovePacman();
    void Update(float dt);
    bool CollidesWithPacman(std::shared_ptr<Entity> entity, float dt) const;

    void Render();

    std::vector<std::shared_ptr<Entity>> getEntities();

    ~World() = default;
private:
    std::vector<std::shared_ptr<Entity>> entities;
    std::shared_ptr<Pacman> pacman;
    std::vector<std::vector<bool>> wallGrid;
    std::shared_ptr<EntityFactory> entity_factory;
};



#endif //WORLD_H
