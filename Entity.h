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

class Wall;
class Orb;
class Ghost;
class PacMan;

class Entity {
public:
    Entity() = default;

    virtual void Update(float dt);

    virtual void InteractWithWall() {};
    virtual std::shared_ptr<Entity> InteractWithOrb(std::shared_ptr<Entity> orb) {return nullptr;};
    virtual std::tuple<std::shared_ptr<Entity>, bool, bool> InteractWithGhost(std::shared_ptr<Entity> ghost) {return std::make_tuple(nullptr, false, false);};

    virtual bool isBig() const {return true;};

    virtual void setFeared(bool feared) {};
    virtual bool getFeared() {return true;};

    Position getPosition() const;
    void setPosition(float x, float y);

    virtual ~Entity() = default;
protected:
    Position position;
    std::vector<int> direction;
};



#endif //ENTITY_H
