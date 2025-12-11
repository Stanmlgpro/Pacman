//
// Created by stan on 10/15/25.
//

#include "Orb.h"
#include "Pacman.h"
#include "World.h"
#include <iostream>

namespace entities {
    Orb::Orb(float x, float y) {
        position.x = x;
        position.y = y;
        setCollisionSize(0.85f);
    }

    std::shared_ptr<Entity> Orb::Interact(World& world) {
        return world.CollidesWithPacman(shared_from_this());
    }

    void Orb::Update(float dt) {
        view->Update(dt);
    }

    void Orb::checkWin(bool& check) {
        check = false;
    }
}