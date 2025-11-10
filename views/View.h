//
// Created by stan1 on 06/11/2025.
//

#ifndef VIEW_H
#define VIEW_H
#include <memory>
#include <Camera.h>
#include "../singleton/Random.h"

class Camera;
class Entity;
class View {
public:
    View(std::weak_ptr<Entity> entity, std::shared_ptr<Camera> camera);

    virtual void Update(float dt) = 0;

    virtual void Draw() = 0;
protected:
    std::weak_ptr<Entity> entity;
    std::shared_ptr<Camera> camera;
    Random& random = Random::getInstance();
};



#endif //VIEW_H
