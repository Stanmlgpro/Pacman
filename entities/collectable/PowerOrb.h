//
// Created by stan1 on 11/12/2025.
//

#ifndef POWERORB_H
#define POWERORB_H
#include "./entities/Entity.h"

namespace entities {
class PowerOrb : public Entity, public std::enable_shared_from_this<PowerOrb> {
public:
    PowerOrb(float x, float y);

    std::shared_ptr<Entity> Interact(World& world) override;

    void Update(float dt) override;
    void checkWin(bool& check) override;

    ~PowerOrb() override = default;
};
} // namespace entities

#endif // POWERORB_H
