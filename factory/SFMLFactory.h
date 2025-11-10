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
    SFMLFactory(sf::RenderWindow& window, std::string texture_input, std::shared_ptr<Camera> camera);
    std::shared_ptr<Wall> createWall(float x, float y) override;
    std::shared_ptr<Ghost> createGhost(float x, float y, std::shared_ptr<Pacman> pacman, std::vector<std::vector<bool>> wallGrid, int id, bool first_time) override;
    std::shared_ptr<Orb> createOrb(float x, float y) override;
    std::shared_ptr<Orb> createBigOrb(float x, float y) override;
    std::shared_ptr<Pacman> createPacman(float speed, int mapwidth, int mapheight, float x, float y) override;

    std::shared_ptr<Camera> getCamera();
    ~SFMLFactory() override = default;
private:
    sf::RenderWindow& window;
    sf::Texture texture;
};

#endif //SFMLFACTORY_H
