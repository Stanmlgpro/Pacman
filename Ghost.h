//
// Created by stan on 10/15/25.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "Entity.h"

class Ghost : public Entity, public std::enable_shared_from_this<Ghost> {
public:
    Ghost(int x, int y, std::shared_ptr<Pacman> pacman, const std::vector<std::vector<bool>>& wallgrid, int id);

    void CalculateNextTurn(float dt);

    std::tuple<std::shared_ptr<Entity>, bool, bool> Interact(Pacman& pacman) override;

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