//
// Created by stan1 on 06/11/2025.
//

#include "SFMLWallView.h"
#include "Entity.h"

SFMLWallView::SFMLWallView(const sf::Texture& texture, std::weak_ptr<Entity> entity, sf::RenderWindow& window) : SFMLView(texture, entity, window) {
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
    sprite.setScale(1.f, 1.f);
    sprite.setOrigin(8.f, 8.f);
}

void SFMLWallView::Update(float dt) {}

void SFMLWallView::Draw() {
    auto e = entity.lock();
    if (!e) return;

    sprite.setPosition(e->getPosition().x * 16.f + 8.f, e->getPosition().y * 16.f + 8.f);
    window.draw(sprite);
}

