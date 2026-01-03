//
// Created by stan1 on 06/11/2025.
//

#ifndef SFMLFACTORY_H
#define SFMLFACTORY_H
#include "EntityFactory.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
/**
 * @file SFMLFactory.h
 * @brief SFMLFactory Class
 */
namespace entities {
class Entity;
class Pacman;
} // namespace entities
namespace sprites {
class SpriteAtlas;
}
namespace factory {
    /**
* @class SFMLFactory
* @brief derives from the EntityFactory
*
* Implements all the pure virtual functions and creates specific SFML objects to attach to them.
* Creates SFML views and attaches them to the created entities
*/
class SFMLFactory : public EntityFactory {
public:
    /**
* @brief Creates an SFMLFactory object.
*
* @param window used by created SFMLviews to draw their information
* @param texture_input full texture file given to the views to splice the correct texture
* @param camera used to correctly position all views for all screen sizes
*/
    SFMLFactory(sf::RenderWindow& window, std::string texture_input, std::shared_ptr<Camera> camera);
    /// Overrides EntityFactory::createWall
    std::shared_ptr<entities::Wall> createWall(float x, float y) override;
    /// Overrides EntityFactory::createGhost
    std::shared_ptr<entities::Ghost> createGhost(float x, float y, std::shared_ptr<entities::Pacman> pacman,
                                                 std::vector<std::vector<bool>> wallGrid, int id,
                                                 bool first_time) override;
    /// Overrides EntityFactory::createOrb
    std::shared_ptr<entities::Orb> createOrb(float x, float y) override;
    /// Overrides EntityFactory::createPowerOrb
    std::shared_ptr<entities::PowerOrb> createPowerOrb(float x, float y) override;
    /// Overrides EntityFactory::createFruit
    std::shared_ptr<entities::Fruit> createFruit(float x, float y) override;
    /// Overrides EntityFactory::createPacman
    std::shared_ptr<entities::Pacman> createPacman(float speed, int mapwidth, int mapheight, float x, float y) override;
    /// Overrides EntityFactory::createWorldView
    std::unique_ptr<views::View> createWorldView() override;

    /// Overrides EntityFactory::getCamera
    std::shared_ptr<Camera> getCamera() override;

    ~SFMLFactory() override = default;

private:
    /** Atlas of premade correct rectangles for all needed sprites */
    std::shared_ptr<sprites::SpriteAtlas> atlas;
    sf::RenderWindow& window;
    sf::Texture texture;
};
} // namespace factory

#endif // SFMLFACTORY_H
