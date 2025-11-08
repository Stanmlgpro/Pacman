//
// Created by stan1 on 13/10/2025.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <memory>
#include <vector>
#include "View.h"

struct Position {
    float x;
    float y;
};

class Wall;
class Orb;
class Ghost;
class Pacman;

class Entity {
public:
    Entity() = default;
    Entity(int mapwidth, int mapheight);

    virtual void Update(float dt);

    void Draw();

    virtual std::tuple<std::shared_ptr<Entity>, bool, bool> Interact(Pacman& pacman) = 0;

    virtual bool isBig() const {return true;}

    void setView(std::unique_ptr<View> view);

    virtual void setFeared(bool feared) {}
    virtual bool getFeared() {return true;}

    Position getPosition() const;
    void setPosition(float x, float y);

    std::vector<int> getDirection() const;
    virtual void setDirection(std::vector<int> direction);

    virtual ~Entity() = default;
protected:
    Position position;
    std::vector<int> direction;
    std::unique_ptr<View> view;
    int mapwidth;
    int mapheight;
};



#endif //ENTITY_H
