//
// Created by stan on 10/15/25.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "entities/Entity.h"

class Ghost : public Entity, public std::enable_shared_from_this<Ghost> {
public:
    Ghost(float x, float y, std::shared_ptr<Pacman> pacman, const std::vector<std::vector<bool>>& wallgrid, int id);

    void CalculateNextTurn(float dt);

    std::shared_ptr<Entity> Interact(World& world) override;

    void Update(float dt) override;

    void setFeared(bool feared);
    bool getFeared();

    ~Ghost() override = default;
private:
    std::shared_ptr<Pacman> pacman;
    std::vector<std::vector<bool>> wallgrid;
    bool feared = false;
    int id;
};


#endif //PACMAN_GHOST_H