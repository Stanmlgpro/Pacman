//
// Created by stan1 on 08/11/2025.
//

#ifndef SFMLLOCKEDGHOSTVIEW_H
#define SFMLLOCKEDGHOSTVIEW_H
#include "SFMLGhostView.h"
/**
 * @file SFMLLockedGhostView.h
 * @brief SFMLLockedGhostView Class
 */
namespace views {
/**
 * @class SFMLLockedGhostView
 * @brief Specific Ghost derived from SFMLGhostView
 */
class SFMLLockedGhostView : public SFMLGhostView {
public:
    /**
     * @brief Creates a SFMLLockedGhostView object.
     * @param texture texture of which to get the sprites
     * @param atlas atlast from where we get the correct rectangles to get our sprites from
     * @param entity weak pointer to the entity of which this view belongs to
     * @param window window to draw the sprites onto
     * @param camera camera to calculate the correct position to draw the sprites
     */
    SFMLLockedGhostView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                        std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window,
                        std::shared_ptr<Camera> camera);
    /// Overrides SFMLView::FindSprite
    void FindSprite() override;

    ~SFMLLockedGhostView() override = default;
};
} // namespace views
#endif // SFMLLOCKEDGHOSTVIEW_H
