//
// Created by stan1 on 11/12/2025.
//

#ifndef SFMLPOWERORBVIEW_H
#define SFMLPOWERORBVIEW_H
#include <views/SFMLView.h>

namespace views {
class SFMLPowerOrbView : public SFMLView {
public:
    SFMLPowerOrbView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                     std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);

    void Update(float dt) override;
    void FindSprite() override;

    void Draw() override;

    ~SFMLPowerOrbView() override = default;
};
} // namespace views

#endif // SFMLPOWERORBVIEW_H
