//
// Created by stan1 on 13/10/2025.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <memory>

struct Position {
    float x;
    float y;
};

class Entity {
public:
    Entity() = default;

    virtual void Update(float dt) = 0;
    virtual void Interact(std::shared_ptr<Entity> other) = 0;

    ~Entity() = default;
private:
    Position position;
};



#endif //ENTITY_H
