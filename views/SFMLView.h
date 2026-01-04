//
// Created by stan1 on 06/11/2025.
//

#ifndef SFMLVIEW_H
#define SFMLVIEW_H
#include "View.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <factory/SpriteAtlas.h>
#include <string>
/**
 * @file SFMLView.h
 * @brief SFMLView Class
 */
namespace views {
/**
 * @class SFMLView
 * @brief Main SFMLView class
 *
 * Parent of all SFMLViews
 */
class SFMLView : public View {
public:
    /**
     * @brief Creates a SFMLView object.
     * @param texture texture of which to get the sprites
     * @param atlas atlast from where we get the correct rectangles to get our sprites from
     * @param entity weak pointer to the entity of which this view belongs to
     * @param window window to draw the sprites onto
     * @param camera camera to calculate the correct position to draw the sprites
     */
    SFMLView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
             std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
    /**
     * @brief Updates the view
     *
     * pure virtual, responsible for updating all animation variables
     * choosing the correct sprite for the current frame using the atlas
     *
     * @param dt amount the animations should be moving
     */
    void Update(float dt) override = 0;
    /**
     * @brief Finds the sprites
     *
     * pure virtual, responsible for finding the correct sprite
     * uses the atlas to ask it for the correct rectangle based on spriteID
     */
    virtual void FindSprite() = 0;
    /**
     * @brief Draws the sprites
     *
     * pure virtual, responsible for drawing the sprite
     * uses the camera class to find the correct position and scaling
     * sets the correct origin and uses the camera to draw the sprite onto the screen
     */
    void Draw() override = 0;

    ~SFMLView() override = default;

protected:
    /** holds the sprite and texture to be drawn */
    sf::Sprite sprite;
    sf::Texture texture;
    /** holds the atlas for correct rectangle computation */
    std::shared_ptr<sprites::SpriteAtlas> atlas;
    /** holds the window to draw on */
    sf::RenderWindow& window;
};
} // namespace views

#endif // SFMLVIEW_H
