//
// Created by stan1 on 09/11/2025.
//

#ifndef SFMLPREDICTGHOST2VIEW_H
#define SFMLPREDICTGHOST2VIEW_H
#include "SFMLGhostView.h"
/**
 * @file SFMLPredictGhost2View.h
 * @brief SFMLPredictGhost2View Class
 */
namespace views {
    /**
* @class SFMLPredictGhost2View
* @brief Specific Ghost derived from SFMLGhostView
*/
class SFMLPredictGhost2View : public SFMLGhostView {
public:
    /**
* @brief Creates a SFMLPredictGhost2View object.
* @param texture texture of which to get the sprites
* @param atlas atlast from where we get the correct rectangles to get our sprites from
* @param entity weak pointer to the entity of which this view belongs to
* @param window window to draw the sprites onto
* @param camera camera to calculate the correct position to draw the sprites
*/
    SFMLPredictGhost2View(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                          std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window,
                          std::shared_ptr<Camera> camera);
    /// Overrides SFMLView::FindSprite
    void FindSprite() override;

    ~SFMLPredictGhost2View() override = default;
};
} // namespace views

#endif // SFMLPREDICTGHOST2VIEW_H
