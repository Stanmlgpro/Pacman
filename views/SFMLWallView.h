//
// Created by stan1 on 06/11/2025.
//

#ifndef SFMLWALLVIEW_H
#define SFMLWALLVIEW_H
#include <views/SFMLView.h>

namespace views {
class SFMLWallView : public SFMLView {
public:
    SFMLWallView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                 std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);

    void Update(float dt) override;
    void FindSprite() override {}

    void Draw() override;

    ~SFMLWallView() override = default;
private:
    sf::Sprite sprite;
    sf::RectangleShape rect;
};
} // namespace views

#endif // SFMLWALLVIEW_H
