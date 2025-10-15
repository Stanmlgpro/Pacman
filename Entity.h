//
// Created by stan1 on 13/10/2025.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <memory>
#include <vector>

struct Position {
    float x;
    float y;
};

class Entity {
public:
    Entity() = default;

    virtual void Update(float dt);
    virtual void Interact(std::shared_ptr<Entity> other) = 0;

    ~Entity() = default;
private:
    Position position;
    std::vector<int> direction;
};



#endif //ENTITY_H
