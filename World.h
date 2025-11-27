//
// Created by stan1 on 14/10/2025.
//

#ifndef WORLD_H
#define WORLD_H
#include <memory>
#include <string>

#include "Score.h"
#include "entities/Entity.h"
#include "sounds/WorldSound.h"

namespace factory {
    class EntityFactory;
}

enum MOVE {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class World {
public:
    explicit World(std::string filename, std::shared_ptr<factory::EntityFactory> entity_factory, std::shared_ptr<WorldSound> world_sounds, std::string player);

    void loadMap_reset();
    bool Update();
    std::shared_ptr<entities::Entity> CollidesWithPacman(std::shared_ptr<entities::Wall> wall);
    std::shared_ptr<entities::Entity> CollidesWithPacman(std::shared_ptr<entities::Orb> orb);
    std::shared_ptr<entities::Entity> CollidesWithPacman(std::shared_ptr<entities::Ghost> ghost);
    std::shared_ptr<entities::Entity> CollidesWithPacman(std::shared_ptr<entities::Pacman> pacman);

    bool WouldHitWall(const std::vector<int>& direction) const;
    void TryBuffer();
    static std::vector<int> NormalizedToGrid(float normX, float normY, std::vector<std::vector<bool>> wallGrid);
    void Render();
    void movePacman(MOVE movement);

    std::vector<std::shared_ptr<entities::Entity>> getEntities();

    ~World() = default;
private:
    std::string filename;
    std::vector<std::shared_ptr<entities::Entity>> entities;
    std::shared_ptr<entities::Pacman> pacman;
    std::vector<std::vector<bool>> wallGrid;
    std::shared_ptr<factory::EntityFactory> entity_factory;
    std::shared_ptr<WorldSound> world_sounds;
    std::vector<std::shared_ptr<entities::Entity>> to_add;
    float dt;
    bool fearmode = false;
    float ghost_speed_mul;
    float fear_time;
    float fear_timer;
    std::unique_ptr<Score> score;
    int difficulty;
};



#endif //WORLD_H
