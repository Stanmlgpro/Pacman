//
// Created by stan on 10/15/25.
//

#ifndef PACMAN_ORB_H
#define PACMAN_ORB_H
#include "Entity.h"

class Orb : public Entity {
public:
    Orb(int x, int y, bool big);

    std::tuple<std::shared_ptr<Entity>, bool, bool> Interact(Pacman& pacman) override;

    bool isBig() const override;

    ~Orb() override = default;
private:
    bool big;
};


#endif //PACMAN_ORB_H