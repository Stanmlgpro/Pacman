//
// Created by stan1 on 06/11/2025.
//

#include "SFMLWallView.h"
#include "Entity.h"

SFMLWallView::SFMLWallView(const sf::Texture& texture, std::weak_ptr<Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera) : SFMLView(texture, entity, window, camera) {
    rect.setFillColor(sf::Color(0, 0, 180));
}

void SFMLWallView::Update(float dt) {}

void SFMLWallView::Draw() {
    auto e = entity.lock();
    if (!e) return;

    auto screensize = camera->getSpritePixelSize();
    auto screenpos = camera->worldToPixel(e->getPosition().x, e->getPosition().y);

    // Update size, origin, and position together each frame
    rect.setSize(sf::Vector2f(screensize.x, screensize.y));
    rect.setOrigin(screensize.x / 2.f, screensize.y / 2.f);  // Center origin based on current size
    rect.setPosition(screenpos.x, screenpos.y);

    window.draw(rect);
}

