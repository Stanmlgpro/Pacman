//
// Created by stan on 10/15/25.
//

#ifndef PACMAN_ORB_H
#define PACMAN_ORB_H
#include "./entities/Entity.h"

namespace entities {
    class Orb : public Entity, public std::enable_shared_from_this<Orb> {
    public:
        Orb(float x, float y);

        std::shared_ptr<Entity> Interact(World& world) override;

        void Update(float dt) override;
        void checkWin(bool& check) override;

        ~Orb() override = default;
    };
}

#endif //PACMAN_ORB_H