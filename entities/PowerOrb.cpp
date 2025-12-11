//
// Created by stan1 on 11/12/2025.
//

#include "PowerOrb.h"
#include "World.h"

namespace entities {
    PowerOrb::PowerOrb(float x, float y) {
        position.x = x;
        position.y = y;
        setCollisionSize(1.25f);
    }

    std::shared_ptr<Entity> PowerOrb::Interact(World& world) {
        return world.CollidesWithPacman(shared_from_this());
    }

    void PowerOrb::Update(float dt) {
        view->Update(dt);
    }

    void PowerOrb::checkWin(bool& check) {
        check = false;
    }
}
