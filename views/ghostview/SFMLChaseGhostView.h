//
// Created by stan1 on 09/11/2025.
//

#ifndef SFMLCHASEGHOSTVIEW_H
#define SFMLCHASEGHOSTVIEW_H
#include "SFMLGhostView.h"
/**
 * @file SFMLChaseGhostView.h
 * @brief SFMLChaseGhostView Class
 */
namespace views {
/**
 * @class SFMLChaseGhostView
 * @brief Specific Ghost derived from SFMLGhostView
 */
class SFMLChaseGhostView final : public SFMLGhostView {
public:
    /**
     * @brief Creates a SFMLChaseGhostView object.
     * @param texture texture of which to get the sprites
     * @param atlas atlast from where we get the correct rectangles to get our sprites from
     * @param entity weak pointer to the entity of which this view belongs to
     * @param window window to draw the sprites onto
     * @param camera camera to calculate the correct position to draw the sprites
     */
    SFMLChaseGhostView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                       std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window,
                       std::shared_ptr<Camera> camera);
    /// Overrides SFMLView::FindSprite
    void FindSprite() override;

    ~SFMLChaseGhostView() override = default;
};
} // namespace views

#endif // SFMLCHASEGHOSTVIEW_H
