//
// Created by stan1 on 06/11/2025.
//

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H
#include "Camera.h"
#include "entities/ghost/Ghost.h"
#include <memory>
#include <vector>
/**
 * @file EntityFactory.h
 * @brief EntityFactory Class
 */
namespace entities {
class Entity;
class Pacman;
} // namespace entities

namespace factory {
/**
 * @class EntityFactory
 * @brief Base class to derive from and implement
 *
 * Basic framework to create entities
 */
class EntityFactory {
public:
    /**
     * @brief creates a wall
     *
     * @param x x position
     * @param y y position
     *
     * @return created wall
     */
    virtual std::shared_ptr<entities::Wall> createWall(float x, float y) = 0;
    /**
     * @brief creates a Ghost
     *
     * @param x x position
     * @param y y position
     * @param pacman pacman object to get its status
     * @param wallGrid 2D vector of bools that represent the existing walls, used to prevent phasing trough them
     * @param id in (1,2,3,4) decides when a ghost can start chasing pacman
     * @param first_time bool to check if this is the first time this entity is created
     *
     * @return created Ghost
     */
    virtual std::shared_ptr<entities::Ghost> createGhost(float x, float y, std::shared_ptr<entities::Pacman> pacman,
                                                         std::vector<std::vector<bool>> wallGrid, int id,
                                                         bool first_time) = 0;
    /**
     * @brief creates an Orb
     *
     * @param x x position
     * @param y y position
     *
     * @return created Orb
     */
    virtual std::shared_ptr<entities::Orb> createOrb(float x, float y) = 0;
    /**
     * @brief creates a PowerOrb
     *
     * @param x x position
     * @param y y position
     *
     * @return created PowerOrb
     */
    virtual std::shared_ptr<entities::PowerOrb> createPowerOrb(float x, float y) = 0;
    /**
     * @brief creates a Fruit
     *
     * @param x x position
     * @param y y position
     *
     * @return created Fruit
     */
    virtual std::shared_ptr<entities::Fruit> createFruit(float x, float y) = 0;
    /**
     * @brief creates Pacman
     *
     * @param speed speed at which pacman will move
     * @param mapwidth width of the map, used for calculation
     * @param mapheight height of the map, used for calculation
     * @param x x position
     * @param y y position
     *
     * @return Pacman
     */
    virtual std::shared_ptr<entities::Pacman> createPacman(float speed, int mapwidth, int mapheight, float x,
                                                           float y) = 0;
    /**
     * @brief creates a worldview
     *
     * creates the view that the world will use to display scoring etc...
     *
     * @return created worldview
     */
    virtual std::unique_ptr<views::View> createWorldView() = 0;
    /**
     * @return returns the camera
     */
    virtual std::shared_ptr<Camera> getCamera() = 0;

    virtual ~EntityFactory() = default;

protected:
    /** used for correct positioning for all screen sizes */
    std::shared_ptr<Camera> camera;
};
} // namespace factory

#endif // ENTITYFACTORY_H
