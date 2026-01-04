//
// Created by stan1 on 14/10/2025.
//

#ifndef WORLD_H
#define WORLD_H
#include <entities/collectable/Fruit.h>
#include <memory>
#include <string>

#include "Score.h"
#include "entities/Entity.h"
#include "sounds/WorldSound.h"
/**
 * @file World.h
 * @brief World Class
 */
namespace factory {
class EntityFactory;
}
namespace views {
class View;
}
/**
 * @enum MOVE
 * @brief all possible moves for pacman
 */
enum MOVE { UP, DOWN, LEFT, RIGHT };
/**
 * @class World
 * @brief class the orchestrates the actual game
 */
class World : public std::enable_shared_from_this<World> {
public:
    /**
     * @brief Creates a StateManager object.
     * @param filename File from which we read the map
     * @param entity_factory Reference to the entity_factory so we can gcreate the necessary entites
     * @param world_sounds Reference to the world_sounds so we can create the necessary sounds
     * @param player to give to the Score class
     */
    explicit World(std::string filename, const std::shared_ptr<factory::EntityFactory>& entity_factory,
                   std::shared_ptr<sounds::WorldSound> world_sounds, const std::string& player);

    /**
     * @brief Called when a new map needs to be loaded
     *
     * reads from the file and creates the correct objects using the entity_factory
     * also called when a level is won, and we need to go to a new level
     * also upgrades the difficulty by shortening fearmode and increasing ghost speed
     */
    void loadMap_reset();
    /**
     * @brief Updates the game and its entities
     *
     * first calculates the new dt using the Stopwatch
     * then checks for a won or lost game and tries the buffered input
     * then test all collisions, removes all deleted entities and updates all the rest
     */
    bool Update();
    /**
     * @brief tests if a specific entity is interaction with pacman
     *
     * calculates whether are not pacman is hitting an entity
     * then deletes, adds scoring, ... based on which entity hits pacman
     */
    /// @{
    std::shared_ptr<entities::Entity> CollidesWithPacman(const std::shared_ptr<entities::Wall>& wall) const;
    std::shared_ptr<entities::Entity> CollidesWithPacman(std::shared_ptr<entities::Orb> orb) const;
    std::shared_ptr<entities::Entity> CollidesWithPacman(std::shared_ptr<entities::PowerOrb> powerorb);
    std::shared_ptr<entities::Entity> CollidesWithPacman(std::shared_ptr<entities::Fruit> fruit,
                                                         sprites::Sprite_ID ID) const;
    std::shared_ptr<entities::Entity> CollidesWithPacman(const std::shared_ptr<entities::Ghost>& ghost);

    /**
     * @brief only here for completeness, is logically never called
     */
    static std::shared_ptr<entities::Entity> CollidesWithPacman(std::shared_ptr<entities::Pacman> pacman);
    /// @}

    /**
     * @brief checks the inputted buffer
     *
     * snaps pacman to grid, checks if the direction would be possible if we were at that point
     * swaps the direction in for the buffer is we are close enough to the tile center
     */
    void TryBuffer();
    /**
     * @brief Helper function
     *
     * calculates the closest tile to the world coords
     */
    static std::vector<int> NormalizedToGrid(float normX, float normY, const std::vector<std::vector<bool>>& wallGrid);
    /**
     * @brief Renders the game
     *
     * renders all the entites
     * renders pacman
     * renders the worldview
     */
    void Render() const;
    /**
     * @brief sets pacman's directions
     *
     * sets the buffered direction of pacman to whatever was inputted
     */
    void movePacman(MOVE movement) const;

    /**
     * @return returns the Entities
     */
    std::vector<std::shared_ptr<entities::Entity>> getEntities();
    /**
     * @return returns the amount of Lives
     */
    int getLives() const;
    /**
     * @return returns the Score
     */
    int getScore() const;
    /**
     * @brief pauses the game's sounds
     */
    void Pause();
    /**
     * @brief resumes the game's sounds
     */
    void Resume();

    ~World();

private:
    std::string filename;
    std::vector<std::shared_ptr<entities::Entity>> entities;
    std::shared_ptr<entities::Pacman> pacman;
    std::vector<std::vector<bool>> wallGrid;
    std::shared_ptr<factory::EntityFactory> entity_factory;
    std::shared_ptr<sounds::WorldSound> world_sounds;
    std::unique_ptr<views::View> world_view;
    std::vector<std::shared_ptr<entities::Entity>> to_add;
    float dt;
    bool fearmode = false;
    bool gamelost = false;
    float ghost_speed_mul;
    float fear_time;
    float fear_timer;
    bool paused = false;
    std::unique_ptr<Score> score;
    /** used to decrease fearmode length and increase ghost speeds */
    int difficulty;
    /** used to calculate the correct score of ghost eating based on the ghost eaten before */
    /// @{
    int combo = -1;
    float combo_timer;
    float combo_time;
    /// @}
};

#endif // WORLD_H
