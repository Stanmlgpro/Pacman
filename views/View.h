//
// Created by stan1 on 06/11/2025.
//

#ifndef VIEW_H
#define VIEW_H
#include "../singleton/Random.h"
#include <Camera.h>
#include <entities/Position.h>
#include <memory>
/**
 * @file View.h
 * @brief View Class
 */
namespace entities {
class Entity;
}
namespace sprites {
enum class Sprite_ID;
}

class World;
class Camera;
namespace views {
/**
 * @class View
 * @brief Main View class
 *
 * Parent View class
 */
class View {
public:
    /**
     * @brief Creates a View object.
     * @param entity weak pointer to the entity of which this view belongs to
     * @param camera camera to calculate the correct position to draw the sprites
     */
    View(std::weak_ptr<entities::Entity> entity, std::shared_ptr<Camera> camera);
    /**
     * @brief Updates the view
     * @param dt delta time
     */
    virtual void Update(float dt) = 0;
    /** here to be overwritten by SFMLWorldView */
    /// @{
    virtual void setLives(int lives) {};
    virtual void setScore(int score) {};
    virtual void ItemEaten(sprites::Sprite_ID ID, Position position) {};
    /// @}

    /**
     * @brief Draws the view
     */
    virtual void Draw() = 0;

    virtual ~View() = default;

protected:
    std::weak_ptr<entities::Entity> entity;
    std::shared_ptr<Camera> camera;
    /** Random present to break ties and make decisions */
    singleton::Random& random = singleton::Random::getInstance();
};
} // namespace views

#endif // VIEW_H
