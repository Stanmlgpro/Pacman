//
// Created by stan1 on 06/11/2025.
//

#include "SFMLWallView.h"
#include "Entity.h"
#include <iostream>

SFMLWallView::SFMLWallView(const sf::Texture& texture, std::weak_ptr<Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera) : SFMLView(texture, entity, window, camera) {
    rect.setSize(sf::Vector2f(16.f, 16.f));
    rect.setOrigin(8.f, 8.f);
    rect.setFillColor(sf::Color(0, 0, 180));
    auto screensize = camera->getSpritePixelSize();
    rect.setOrigin(screensize.x/2, screensize.y/2);
}

void SFMLWallView::Update(float dt) {}

void SFMLWallView::Draw() {
    auto e = entity.lock();
    if (!e) return;

    auto screensize = camera->getSpritePixelSize();
    auto screenpos = camera->worldToPixel(e->getPosition().x, e->getPosition().y);
    rect.setSize(sf::Vector2f(screensize.x, screensize.y));
    rect.setPosition(screenpos.x, screenpos.y);

    window.draw(rect);
}

