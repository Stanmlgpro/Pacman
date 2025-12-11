//
// Created by stan1 on 06/11/2025.
//

#include "SFMLView.h"
namespace views {
    SFMLView::SFMLView(const sf::Texture& texture, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera) : View(std::move(entity), std::move(camera)), texture(texture), window(window) {}
}