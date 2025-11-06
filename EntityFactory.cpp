//
// Created by stan1 on 06/11/2025.
//

#include "EntityFactory.h"
#include "Wall.h"
#include "Ghost.h"
#include "Orb.h"
#include "Pacman.h"

std::shared_ptr<Entity> SFMLFactory::createWall(int x, int y) {
    auto wall = std::make_shared<Wall>(x, y);
    return wall;
}
std::shared_ptr<Entity> SFMLFactory::createOrb(int x, int y) {
    auto orb = std::make_shared<Orb>(x, y, false);
    return orb;
}
std::shared_ptr<Entity> SFMLFactory::createBigOrb(int x, int y) {
    auto orb = std::make_shared<Orb>(x, y, true);
    return orb;
}
std::shared_ptr<Entity> SFMLFactory::createGhost(int x, int y, std::shared_ptr<Pacman> pacman, std::vector<std::vector<bool>> wallGrid, int id) {
    auto ghost = std::make_shared<Ghost>(x, y, pacman, wallGrid, id);
    return ghost;
}
std::shared_ptr<Pacman> SFMLFactory::createPacman(int x, int y) {
    auto pacman = std::make_shared<Pacman>(x, y);
    return pacman;
}
