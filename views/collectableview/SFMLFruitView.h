//
// Created by stan1 on 12/12/2025.
//

#ifndef SFMLFRUITVIEW_H
#define SFMLFRUITVIEW_H
#include <views/SFMLView.h>
/**
 * @file SFMLFruitView.h
 * @brief SFMLFruitView Class
 */
namespace views {
/**
 * @class SFMLFruitView
 * @brief Main FruitView class
 *
 * Parent of all SFMLViews related to fruits.
 */
class SFMLFruitView : public SFMLView {
public:
    /**
     * @brief Creates a SFMLFruitView object.
     * @param texture texture of which to get the sprites
     * @param atlas atlast from where we get the correct rectangles to get our sprites from
     * @param entity weak pointer to the entity of which this view belongs to
     * @param window window to draw the sprites onto
     * @param camera camera to calculate the correct position to draw the sprites
     */
    SFMLFruitView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                  std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
    /// Overrides SFMLView::Update
    void Update(float dt) override;
    /// Overrides SFMLView::Draw
    void Draw() override;

    ~SFMLFruitView() override = default;
};

/**
 * @class SFMLCherryView
 * @brief Cherry fruit
 */
class SFMLCherryView final : public SFMLFruitView {
public:
    SFMLCherryView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                   std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
    /// Overrides SFMLView::FindSprite
    void FindSprite() override;
};
/**
 * @class SFMLStrawberryView
 * @brief Strawberry fruit
 */
class SFMLStrawberryView final : public SFMLFruitView {
public:
    SFMLStrawberryView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                       std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window,
                       std::shared_ptr<Camera> camera);
    /// Overrides SFMLView::FindSprite
    void FindSprite() override;
};
/**
 * @class SFMLMelonView
 * @brief Melon fruit
 */
class SFMLMelonView final : public SFMLFruitView {
public:
    SFMLMelonView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                  std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
    /// Overrides SFMLView::FindSprite
    void FindSprite() override;
};
/**
 * @class SFMLAppleView
 * @brief Apple fruit
 */
class SFMLAppleView final : public SFMLFruitView {
public:
    SFMLAppleView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                  std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
    /// Overrides SFMLView::FindSprite
    void FindSprite() override;
};
/**
 * @class SFMLOrangeView
 * @brief Orange fruit
 */
class SFMLOrangeView final : public SFMLFruitView {
public:
    SFMLOrangeView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                   std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
    /// Overrides SFMLView::FindSprite
    void FindSprite() override;
};
/**
 * @class SFMLGalaxianView
 * @brief Galaxian fruit
 */
class SFMLGalaxianView final : public SFMLFruitView {
public:
    SFMLGalaxianView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                     std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
    /// Overrides SFMLView::FindSprite
    void FindSprite() override;
};
/**
 * @class SFMLBellView
 * @brief Bell fruit
 */
class SFMLBellView final : public SFMLFruitView {
public:
    SFMLBellView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                 std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
    /// Overrides SFMLView::FindSprite
    void FindSprite() override;
};
/**
 * @class SFMLKeyView
 * @brief Key fruit
 */
class SFMLKeyView final : public SFMLFruitView {
public:
    SFMLKeyView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
    /// Overrides SFMLView::FindSprite
    void FindSprite() override;
};
} // namespace views

#endif // SFMLFRUITVIEW_H
