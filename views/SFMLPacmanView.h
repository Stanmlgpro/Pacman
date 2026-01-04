//
// Created by stan1 on 06/11/2025.
//

#ifndef SFMLPACMANVIEW_H
#define SFMLPACMANVIEW_H
#include "SFMLView.h"
/**
 * @file SFMLPacmanView.h
 * @brief SFMLPacmanView Class
 */
namespace views {
/**
 * @class SFMLPacmanView
 * @brief Main character view class
 *
 * responsible for visualising our main character (pacman)
 */
class SFMLPacmanView final : public SFMLView {
public:
    /**
     * @brief Creates a SFMLPacmanView object.
     * @param texture texture of which to get the sprites
     * @param atlas atlast from where we get the correct rectangles to get our sprites from
     * @param entity weak pointer to the entity of which this view belongs to
     * @param window window to draw the sprites onto
     * @param camera camera to calculate the correct position to draw the sprites
     */
    SFMLPacmanView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
    std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
    /// Overrides SFMLView::Update
    void Update(float dt) override;
    /// Overrides SFMLView::FindSprite
    void FindSprite() override;
    /// Overrides SFMLView::Draw
    void Draw() override;

    ~SFMLPacmanView() override = default;

private:
    /** boolean values and floats for animations */
    bool open;
    float animation_speed;
    float animation_counter;
    float current_dying_frame = 0;
};
} // namespace views

#endif // SFMLPACMANVIEW_H
