//
// Created by stan1 on 06/11/2025.
//
#include "SFMLPacmanView.h"
#include "Entity.h"
#include <iostream>

SFMLPacmanView::SFMLPacmanView(const sf::Texture& texture, std::weak_ptr<Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera) : SFMLView(texture, entity, window, camera) {
    sprite.setTexture(texture);
    sprite.setScale(1.f, 1.f);
    sprite.setOrigin(8.f,8.f);
    open = true;
    animation_speed = 500;
    animation_counter = 0;
}

void SFMLPacmanView::Update(float dt) {}

void SFMLPacmanView::Draw() {
    animation_counter++;
    if (animation_counter > animation_speed) {
        open = not open;
        animation_counter = 0;
    }
    if (open) sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
    else sprite.setTextureRect(sf::IntRect(15, 0, 16, 16));
    auto e = entity.lock();
    if (!e) return;

    auto screensize = camera->getSpritePixelSize();
    auto screenpos = camera->worldToPixel(e->getPosition().x, e->getPosition().y);
    sprite.setScale(screensize.x / 16.f, screensize.y / 16.f);
    sprite.setPosition(screenpos.x, screenpos.y);

    window.draw(sprite);
}