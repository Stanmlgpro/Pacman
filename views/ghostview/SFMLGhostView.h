//
// Created by stan1 on 08/11/2025.
//

#ifndef SFMLGHOSTVIEW_H
#define SFMLGHOSTVIEW_H
#include "views/SFMLView.h"
/**
 * @file SFMLGhostView.h
 * @brief SFMLGhostView Class
 */
namespace views {
/**
 * @class SFMLGhostView
 * @brief Main SFMLGhostView class
 *
 * Parent of all SFMLViews related to ghosts.
 */
class SFMLGhostView : public SFMLView {
public:
    /**
     * @brief Creates a SFMLGhostView object.
     * @param texture texture of which to get the sprites
     * @param atlas atlast from where we get the correct rectangles to get our sprites from
     * @param entity weak pointer to the entity of which this view belongs to
     * @param window window to draw the sprites onto
     * @param camera camera to calculate the correct position to draw the sprites
     */
    SFMLGhostView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                  std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
    /// Overrides SFMLView::Update
    void Update(float dt) override;
    /// Overrides SFMLView::FindSprite
    void FindSprite() override = 0;
    /// Overrides SFMLView::Draw
    void Draw() override;

    ~SFMLGhostView() override = default;

protected:
    /** booleans and floats to get the correct animation */
    bool animation_bool;
    float animation_speed;
    float animation_counter;
    bool animation_bool_feared;
    float animation_speed_feared;
    float animation_counter_feared;
};
} // namespace views

#endif // SFMLGHOSTVIEW_H
