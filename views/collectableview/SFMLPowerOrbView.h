//
// Created by stan1 on 11/12/2025.
//

#ifndef SFMLPOWERORBVIEW_H
#define SFMLPOWERORBVIEW_H
#include <views/SFMLView.h>
/**
 * @file SFMLPowerOrbView.h
 * @brief SFMLPowerOrbView Class
 */
namespace views {
    /**
* @class SFMLPowerOrbView
* @brief class to visualise PowerOrbs
*/
class SFMLPowerOrbView : public SFMLView {
public:
    /**
* @brief Creates a SFMLPowerOrbView object.
* @param texture texture of which to get the sprites
* @param atlas atlast from where we get the correct rectangles to get our sprites from
* @param entity weak pointer to the entity of which this view belongs to
* @param window window to draw the sprites onto
* @param camera camera to calculate the correct position to draw the sprites
*/
    SFMLPowerOrbView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                     std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
    /// Overrides SFMLView::Update
    void Update(float dt) override;
    /// Overrides SFMLView::FindSprite
    void FindSprite() override;
    /// Overrides SFMLView::Draw
    void Draw() override;

    ~SFMLPowerOrbView() override = default;
};
} // namespace views

#endif // SFMLPOWERORBVIEW_H
