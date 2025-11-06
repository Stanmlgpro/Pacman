//
// Created by stan1 on 06/11/2025.
//

#include "SFMLView.h"

SFMLView::SFMLView(const sf::Texture& texture, std::weak_ptr<Entity> entity, sf::RenderWindow& window) : View(std::move(entity)), texture(texture), window(window) {}
