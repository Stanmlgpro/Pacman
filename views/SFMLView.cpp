//
// Created by stan1 on 06/11/2025.
//

#include "SFMLView.h"

#include <utility>
namespace views {
SFMLView::SFMLView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                   std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera)
    : View(std::move(entity), std::move(camera)), atlas(std::move(atlas)), window(window) {
    // set private variables, scale, origin
    sprite.setTexture(texture);
    this->texture = texture;
    sprite.setScale(1.f, 1.f);
    sprite.setOrigin(8.f, 8.f);
}
} // namespace views