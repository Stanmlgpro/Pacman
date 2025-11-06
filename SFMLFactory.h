//
// Created by stan1 on 06/11/2025.
//

#ifndef SFMLFACTORY_H
#define SFMLFACTORY_H
#include <memory>
#include <vector>
#include "EntityFactory.h"
#include <SFML/Graphics.hpp>

class Entity;
class Pacman;

class SFMLFactory : public EntityFactory {
public:
    SFMLFactory(sf::RenderWindow& window, std::string texture_input);
    std::shared_ptr<Entity> createWall(int x, int y) override;
    std::shared_ptr<Entity> createGhost(int x, int y, std::shared_ptr<Pacman> pacman, std::vector<std::vector<bool>> wallGrid, int id) override;
    std::shared_ptr<Entity> createOrb(int x, int y) override;
    std::shared_ptr<Entity> createBigOrb(int x, int y) override;
    std::shared_ptr<Pacman> createPacman(int x, int y) override;
    ~SFMLFactory() override = default;
private:
    sf::RenderWindow& window;
    sf::Texture texture;
};

#endif //SFMLFACTORY_H
