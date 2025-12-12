//
// Created by stan1 on 06/11/2025.
//

#ifndef SFMLFACTORY_H
#define SFMLFACTORY_H
#include <memory>
#include <vector>
#include "EntityFactory.h"
#include <SFML/Graphics.hpp>

namespace entities {
    class Entity;
    class Pacman;
}
namespace sprites {
    class SpriteAtlas;
}
namespace factory {
    class SFMLFactory : public EntityFactory {
    public:
        SFMLFactory(sf::RenderWindow& window, std::string texture_input, std::shared_ptr<Camera> camera);
        std::shared_ptr<entities::Wall> createWall(float x, float y) override;
        std::shared_ptr<entities::Ghost> createGhost(float x, float y, std::shared_ptr<entities::Pacman> pacman, std::vector<std::vector<bool>> wallGrid, int id, bool first_time) override;
        std::shared_ptr<entities::Orb> createOrb(float x, float y) override;
        std::shared_ptr<entities::PowerOrb> createPowerOrb(float x, float y) override;
        std::shared_ptr<entities::Pacman> createPacman(float speed, int mapwidth, int mapheight, float x, float y) override;
        std::unique_ptr<views::View> createWorldView() override;

        std::shared_ptr<Camera> getCamera();
        ~SFMLFactory() override = default;
    private:
        std::shared_ptr<sprites::SpriteAtlas> atlas;
        sf::RenderWindow& window;
        sf::Texture texture;
    };
}

#endif //SFMLFACTORY_H
