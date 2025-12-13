//
// Created by stan1 on 13/10/2025.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <memory>
#include <vector>
#include "../entities/Position.h"

#include "./views/View.h"
#include "../singleton/Random.h"

class World;
namespace entities {

    class Wall;
    class Orb;
    class PowerOrb;
    class Ghost;
    class Pacman;
    class Fruit;

    class Entity {
    public:
        Entity() = default;
        Entity(int mapwidth, int mapheight);

        static float wrap(float v);
        virtual void Update(float dt) = 0;

        void Draw() const;

        virtual std::shared_ptr<Entity> Interact(World& world) = 0;

        void setView(std::unique_ptr<views::View> view);

        virtual void setFeared(bool feared) {}
        virtual bool getFeared() {return true;}
        virtual float getFearCheck() const {return 0.f;}
        virtual void reset() {}
        virtual void checkWin(bool& check) {};
        virtual bool getDying() const {return false;}

        Position getPosition() const;
        void setPosition(float x, float y);

        std::vector<int> getDirection() const;
        void setDirection(std::vector<int> direction);

        float getCollsionSize() const;
        void setCollisionSize(float size);
        virtual ~Entity() = default;
    protected:
        Position position{};
        std::vector<int> direction;
        std::unique_ptr<views::View> view;
        int mapwidth;
        int mapheight;
        singleton::Random& random = singleton::Random::getInstance();
        float CollisionSize = 0.0f;
    };
}


#endif //ENTITY_H
