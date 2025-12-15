//
// Created by stan1 on 08/11/2025.
//

#ifndef SFMLGHOSTVIEW_H
#define SFMLGHOSTVIEW_H
#include "views/SFMLView.h"

namespace views {
class SFMLGhostView : public SFMLView {
public:
    SFMLGhostView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                  std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);

    void Update(float dt) override;
    void FindSprite() override = 0;

    void Draw() override;

protected:
    bool animation_bool;
    float animation_speed;
    float animation_counter;
    bool animation_bool_feared;
    float animation_speed_feared;
    float animation_counter_feared;
};
} // namespace views

#endif // SFMLGHOSTVIEW_H
