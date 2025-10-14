//
// Created by stan1 on 14/10/2025.
//

#ifndef WORLD_H
#define WORLD_H
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "Entity.h"

class World {
public:
    explicit World(std::string filename);

    void Update(float dt);

    ~World() = default;
private:
    std::shared_ptr<Entity> pacman;
    std::vector<std::shared_ptr<Entity>> ghosts;
    std::vector<std::shared_ptr<Entity>> non_movables;
};



#endif //WORLD_H
