//
// Created by stan1 on 13/10/2025.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <memory>
#include <vector>
#include "./views/View.h"
#include "../singleton/Random.h"

class World;
struct Position {
    float x;
    float y;
};
namespace entities {

    class Wall;
    class Orb;
    class Ghost;
    class Pacman;

    class Entity {
    public:
        Entity() = default;
        Entity(int mapwidth, int mapheight);

        virtual void Update(float dt);

        void Draw() const;

        virtual std::shared_ptr<Entity> Interact(World& world) = 0;

        virtual bool isBig() const {return true;}

        void setView(std::unique_ptr<View> view);

        virtual void setFeared(bool feared) {}
        virtual bool getFeared() {return true;}
        virtual float getFearCheck() const {return 0.f;}
        virtual void reset() {}
        virtual void checkWin(bool& check) {};
        virtual bool getDying() const {return false;}

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
        Random& random = Random::getInstance();
    };
}


#endif //ENTITY_H
