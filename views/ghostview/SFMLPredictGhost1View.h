//
// Created by stan1 on 09/11/2025.
//

#ifndef SFMLPREDICTGHOST1VIEW_H
#define SFMLPREDICTGHOST1VIEW_H
#include "SFMLGhostView.h"
/**
 * @file SFMLPredictGhost1View.h
 * @brief SFMLPredictGhost1View Class
 */
namespace views {
    /**
* @class SFMLPredictGhost1View
* @brief Specific Ghost derived from SFMLGhostView
*/
class SFMLPredictGhost1View : public SFMLGhostView {
public:
    /**
* @brief Creates a SFMLPredictGhost1View object.
* @param texture texture of which to get the sprites
* @param atlas atlast from where we get the correct rectangles to get our sprites from
* @param entity weak pointer to the entity of which this view belongs to
* @param window window to draw the sprites onto
* @param camera camera to calculate the correct position to draw the sprites
*/
    SFMLPredictGhost1View(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                          std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window,
                          std::shared_ptr<Camera> camera);
    /// Overrides SFMLView::FindSprite
    void FindSprite() override;

    ~SFMLPredictGhost1View() override = default;
};
} // namespace views

#endif // SFMLPREDICTGHOST1VIEW_H
