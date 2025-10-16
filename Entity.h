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
class Pacman;

class Entity : public std::enable_shared_from_this<Entity> {
public:
    Entity() = default;

    virtual void Update(float dt);
    virtual std::tuple<std::shared_ptr<Entity>, bool, bool> Interact(Pacman& pacman) = 0;

    virtual bool isBig() const {return true;}

    virtual void setFeared(bool feared) {}
    virtual bool getFeared() {return true;}

    Position getPosition() const;
    void setPosition(float x, float y);

    std::vector<int> getDirection() const;
    void setDirection(std::vector<int> direction);

    virtual ~Entity() = default;
protected:
    Position position;
    std::vector<int> direction;
};



#endif //ENTITY_H
