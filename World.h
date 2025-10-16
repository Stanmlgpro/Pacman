//
// Created by stan1 on 14/10/2025.
//

#ifndef WORLD_H
#define WORLD_H
#include <memory>
#include <string>
#include "Entity.h"

class World {
public:
    explicit World(std::string filename);

    void Update(float dt);
    bool CollidesWithPacman(std::shared_ptr<Entity> entity, float dt) const;

    ~World() = default;
private:
    std::vector<std::shared_ptr<Entity>> entities;
    std::shared_ptr<Pacman> pacman;
    std::vector<std::vector<bool>> wallGrid;
};



#endif //WORLD_H
