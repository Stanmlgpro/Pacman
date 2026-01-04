//
// Created by stan1 on 06/11/2025.
//

#ifndef SFMLWALLVIEW_H
#define SFMLWALLVIEW_H
#include <views/SFMLView.h>
/**
 * @file SFMLWallView.h
 * @brief SFMLWallView Class
 */
namespace views {
/**
 * @class SFMLPacmanView
 * @brief Wall view class
 *
 * responsible for visualising walls
 */
class SFMLWallView final : public SFMLView {
public:
    /**
     * @brief Creates a SFMLWallView object.
     * @param texture texture of which to get the sprites
     * @param atlas atlast from where we get the correct rectangles to get our sprites from
     * @param entity weak pointer to the entity of which this view belongs to
     * @param window window to draw the sprites onto
     * @param camera camera to calculate the correct position to draw the sprites
     */
    SFMLWallView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                 std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
    /// Overrides SFMLView::Update
    void Update(float dt) override;
    /// Overrides SFMLView::FindSprite
    void FindSprite() override {}
    /// Overrides SFMLView::Draw
    void Draw() override;

    ~SFMLWallView() override = default;

private:
    /** rectangle and sprite to draw to visuals the walls */
    sf::Sprite sprite;
    sf::RectangleShape rect;
};
} // namespace views

#endif // SFMLWALLVIEW_H
