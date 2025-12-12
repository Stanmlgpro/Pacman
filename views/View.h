//
// Created by stan1 on 06/11/2025.
//

#ifndef VIEW_H
#define VIEW_H
#include <memory>
#include <Camera.h>
#include "../singleton/Random.h"

namespace entities {
    class Entity;
}

class World;
class Camera;
namespace views {
    class View {
    public:
        View(std::weak_ptr<entities::Entity> entity, std::shared_ptr<Camera> camera);

        virtual void Update(float dt) = 0;
        virtual void setLives(int lives) {};
        virtual void setScore(int score) {};

        virtual void Draw() = 0;
    protected:
        std::weak_ptr<entities::Entity> entity;
        std::shared_ptr<Camera> camera;
        singleton::Random& random = singleton::Random::getInstance();
    };
}


#endif //VIEW_H
