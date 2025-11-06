//
// Created by stan1 on 06/11/2025.
//

#ifndef VIEW_H
#define VIEW_H
#include <memory>

class Entity;
class View {
public:
    View(std::weak_ptr<Entity> entity);

    virtual void Update(float dt) = 0;

    virtual void Draw() = 0;
protected:
    std::weak_ptr<Entity> entity;
};



#endif //VIEW_H
