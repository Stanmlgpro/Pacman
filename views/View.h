//
// Created by stan1 on 06/11/2025.
//

#ifndef VIEW_H
#define VIEW_H
#include "../singleton/Random.h"
#include <Camera.h>
#include <entities/Position.h>
#include <memory>

namespace entities {
class Entity;
}
namespace sprites {
enum class Sprite_ID;
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
    virtual void ItemEaten(sprites::Sprite_ID ID, Position position) {};

    virtual void Draw() = 0;

    virtual ~View() = default;

protected:
    std::weak_ptr<entities::Entity> entity;
    std::shared_ptr<Camera> camera;
    singleton::Random& random = singleton::Random::getInstance();
};
} // namespace views

#endif // VIEW_H
