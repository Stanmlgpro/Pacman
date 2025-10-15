//
// Created by stan on 10/15/25.
//

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "Entity.h"

class Pacman : public Entity {
public:
    Pacman(int x, int y);

    void InteractWithWall() override;
    std::shared_ptr<Entity> InteractWithOrb(std::shared_ptr<Entity> orb) override;
    std::tuple<std::shared_ptr<Entity>, bool, bool> InteractWithGhost(std::shared_ptr<Entity> ghost) override; // returns ghost if needed to be destroyed bool1 : reset, bool2 : game over

    void Update(float dt) override;

    int getLives() const;

    ~Pacman() override = default;
private:
    bool moving = true;
    int lives = 3;
};


#endif //PACMAN_PACMAN_H