//
// Created by stan1 on 09/11/2025.
//

#ifndef SFMLPREDICTGHOST1VIEW_H
#define SFMLPREDICTGHOST1VIEW_H
#include "SFMLGhostView.h"

namespace views {
class SFMLPredictGhost1View : public SFMLGhostView {
public:
    SFMLPredictGhost1View(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                          std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window,
                          std::shared_ptr<Camera> camera);

    void FindSprite() override;

    ~SFMLPredictGhost1View() override = default;
};
} // namespace views

#endif // SFMLPREDICTGHOST1VIEW_H
