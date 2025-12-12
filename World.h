//
// Created by stan1 on 14/10/2025.
//

#ifndef WORLD_H
#define WORLD_H
#include <memory>
#include <string>
#include <entities/collectable/Fruit.h>

#include "Score.h"
#include "entities/Entity.h"
#include "sounds/WorldSound.h"

namespace factory {
    class EntityFactory;
}
namespace views {
    class View;
}

enum MOVE {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class World : public std::enable_shared_from_this<World> {
public:
    explicit World(std::string filename, std::shared_ptr<factory::EntityFactory> entity_factory, std::shared_ptr<sounds::WorldSound> world_sounds, std::string player);

    void loadMap_reset();
    bool Update();
    std::shared_ptr<entities::Entity> CollidesWithPacman(std::shared_ptr<entities::Wall> wall);
    std::shared_ptr<entities::Entity> CollidesWithPacman(std::shared_ptr<entities::Orb> orb);
    std::shared_ptr<entities::Entity> CollidesWithPacman(std::shared_ptr<entities::PowerOrb> powerorb);
    bool CollidesWithPacmanB(std::shared_ptr<entities::Fruit> fruit);
    std::shared_ptr<entities::Entity> CollidesWithPacman(std::shared_ptr<entities::Cherry> fruit);
    std::shared_ptr<entities::Entity> CollidesWithPacman(std::shared_ptr<entities::Strawberry> fruit);
    std::shared_ptr<entities::Entity> CollidesWithPacman(std::shared_ptr<entities::Orange> fruit);
    std::shared_ptr<entities::Entity> CollidesWithPacman(std::shared_ptr<entities::Apple> fruit);
    std::shared_ptr<entities::Entity> CollidesWithPacman(std::shared_ptr<entities::Melon> fruit);
    std::shared_ptr<entities::Entity> CollidesWithPacman(std::shared_ptr<entities::Galaxian> fruit);
    std::shared_ptr<entities::Entity> CollidesWithPacman(std::shared_ptr<entities::Bell> fruit);
    std::shared_ptr<entities::Entity> CollidesWithPacman(std::shared_ptr<entities::Key> fruit);
    std::shared_ptr<entities::Entity> CollidesWithPacman(std::shared_ptr<entities::Ghost> ghost);
    std::shared_ptr<entities::Entity> CollidesWithPacman(std::shared_ptr<entities::Pacman> pacman);

    void TryBuffer();
    static std::vector<int> NormalizedToGrid(float normX, float normY, std::vector<std::vector<bool>> wallGrid);
    void Render();
    void movePacman(MOVE movement);

    std::vector<std::shared_ptr<entities::Entity>> getEntities();
    int getLives() const;
    int getScore() const;

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
    std::unique_ptr<Score> score;
    int difficulty;
    int combo = -1;
    float combo_timer;
    float combo_time;
};



#endif //WORLD_H
