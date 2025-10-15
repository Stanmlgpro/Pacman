//
// Created by stan on 10/15/25.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "Entity.h"

class Ghost : public Entity {
public:
    Ghost(int x, int y, std::shared_ptr<PacMan> pacman, std::vector<std::shared_ptr<Wall>> walls, int id);

    void CalculateNextTurn(float dt);

    void Update(float dt) override;

    void setFeared(bool feared);
    bool getFeared();

    ~Ghost() override = default;
private:
    std::shared_ptr<PacMan> pacman;
    std::vector<std::shared_ptr<Wall>> walls;
    bool feared = false;
    int id;
};


#endif //PACMAN_GHOST_H