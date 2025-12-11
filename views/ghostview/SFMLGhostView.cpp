//
// Created by stan1 on 08/11/2025.
//

#include "SFMLGhostView.h"
#include "entities/Entity.h"
#include <iostream>
namespace views {
    SFMLGhostView::SFMLGhostView(const sf::Texture& texture, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera) : SFMLView(texture, entity, window, camera) {
        sprite.setTexture(texture);
        sprite.setScale(1.f, 1.f);
        sprite.setOrigin(8.f,8.f);
        animation_bool = true;
        animation_speed = 0.1f;
        animation_counter = 0;
        animation_bool_feared = true;
        animation_speed_feared = 0.4f;
        animation_counter_feared = 0;
    }

    void SFMLGhostView::Update(float dt) {
        animation_counter+= dt;
        if (animation_counter > animation_speed) {
            animation_bool = not animation_bool;
            animation_counter = 0;
        }
        if (!entity.lock()->getFeared()) {
            animation_counter_feared = 0;
            animation_bool_feared = false;
        } else {
            animation_counter_feared += dt;
            if (animation_counter_feared > animation_speed_feared) {
                animation_bool_feared = not animation_bool_feared;
                animation_counter_feared = 0;
            }
        }
        FindSprite();
    }

    void SFMLGhostView::Draw() {
        FindSprite();
        auto e = entity.lock();
        if (!e) return;

        auto screensize = camera->getSpritePixelSize();
        auto screenpos = camera->worldToPixel(e->getPosition().x, e->getPosition().y);
        sprite.setScale(screensize.x / 16.f, screensize.y / 16.f);
        sprite.setPosition(screenpos.x, screenpos.y);

        window.draw(sprite);
    }
}