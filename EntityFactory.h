//
// Created by stan1 on 06/11/2025.
//

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H
#include <memory>
#include <vector>

class Entity;
class Pacman;
class EntityFactory {
public:
    virtual std::shared_ptr<Entity> createWall(int x, int y) = 0;
    virtual std::shared_ptr<Entity> createGhost(int x, int y, std::shared_ptr<Pacman>, std::vector<std::vector<bool>> wallGrid, int id) = 0;
    virtual std::shared_ptr<Entity> createOrb(int x, int y) = 0;
    virtual std::shared_ptr<Entity> createBigOrb(int x, int y) = 0;
    virtual std::shared_ptr<Pacman> createPacman(int x, int y) = 0;
    virtual ~EntityFactory() = default;
};

class SFMLFactory : public EntityFactory {
public:
    std::shared_ptr<Entity> createWall(int x, int y) override;
    std::shared_ptr<Entity> createGhost(int x, int y, std::shared_ptr<Pacman> pacman, std::vector<std::vector<bool>> wallGrid, int id) override;
    std::shared_ptr<Entity> createOrb(int x, int y) override;
    std::shared_ptr<Entity> createBigOrb(int x, int y) override;
    std::shared_ptr<Pacman> createPacman(int x, int y) override;
    ~SFMLFactory() override = default;
};

#endif //ENTITYFACTORY_H
