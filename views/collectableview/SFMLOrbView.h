//
// Created by stan1 on 08/11/2025.
//

#ifndef SFMLORBVIEW_H
#define SFMLORBVIEW_H
#include <views/SFMLView.h>
/**
 * @file SFMLOrbView.h
 * @brief SFMLOrbView Class
 */
namespace views {
/**
 * @class SFMLOrbView
 * @brief class to visualise orbs
 */
class SFMLOrbView final : public SFMLView {
public:
    /**
     * @brief Creates a SFMLOrbView object.
     * @param texture texture of which to get the sprites
     * @param atlas atlast from where we get the correct rectangles to get our sprites from
     * @param entity weak pointer to the entity of which this view belongs to
     * @param window window to draw the sprites onto
     * @param camera camera to calculate the correct position to draw the sprites
     */
    SFMLOrbView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
    /// Overrides SFMLView::Update
    void Update(float dt) override;
    /// Overrides SFMLView::FindSprite
    void FindSprite() override;
    /// Overrides SFMLView::Draw
    void Draw() override;

    ~SFMLOrbView() override = default;
};
} // namespace views

#endif // SFMLORBVIEW_H
