//
// Created by stan on 10/15/25.
//

#ifndef PACMAN_ORB_H
#define PACMAN_ORB_H
#include "Entity.h"

class Orb : public Entity, public std::enable_shared_from_this<Orb> {
public:
    Orb(float x, float y, bool big);

    std::shared_ptr<Entity> Interact(World& world) override;

    bool isBig() const override;
    void Update(float dt) override;
    void checkWin(bool& check) override;

    ~Orb() override = default;
private:
    bool big;
};


#endif //PACMAN_ORB_H