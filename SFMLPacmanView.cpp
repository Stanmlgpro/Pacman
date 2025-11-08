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
    animation_speed = 0.1f;
    animation_counter = 0;
}

void SFMLPacmanView::Update(float dt) {
    animation_counter+= dt;
    if (animation_counter > animation_speed) {
        open = not open;
        animation_counter = 0;
    }
    FindSprite();
}

void SFMLPacmanView::FindSprite() {
    auto e = entity.lock();
    if (!e) return;

    int dirX = e->getDirection()[0];
    int dirY = e->getDirection()[1];

    sf::IntRect rect;

    if (dirX == 0 && dirY == -1) {
        rect = open ? sf::IntRect(0, 30, 15, 15) : sf::IntRect(15, 30, 15, 15);
    }
    else if (dirX == 0 && dirY == 1) {
        rect = open ? sf::IntRect(0, 45, 15, 15) : sf::IntRect(15, 45, 15, 15);
    }
    else if (dirX == -1 && dirY == 0) {
        rect = open ? sf::IntRect(0, 15, 15, 15) : sf::IntRect(15, 15, 15, 15);
    }
    else if (dirX == 1 && dirY == 0) {
        rect = open ? sf::IntRect(0, 0, 15, 15) : sf::IntRect(15, 0, 15, 15);
    }
    else {
        rect = sf::IntRect(0, 0, 15, 15);
    }

    sprite.setTextureRect(rect);
}

void SFMLPacmanView::Draw() {

    FindSprite();
    auto e = entity.lock();
    if (!e) return;

    auto screensize = camera->getSpritePixelSize();
    auto screenpos = camera->worldToPixel(e->getPosition().x, e->getPosition().y);
    sprite.setScale(screensize.x / 16.f, screensize.y / 16.f);
    sprite.setPosition(screenpos.x, screenpos.y);

    window.draw(sprite);
}