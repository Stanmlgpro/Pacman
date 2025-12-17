//
// Created by stan1 on 08/11/2025.
//

#ifndef SFMLORBVIEW_H
#define SFMLORBVIEW_H
#include <views/SFMLView.h>

namespace views {
class SFMLOrbView : public SFMLView {
public:
    SFMLOrbView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);

    void Update(float dt) override;
    void FindSprite() override;

    void Draw() override;

    ~SFMLOrbView() override = default;
};
} // namespace views

#endif // SFMLORBVIEW_H
