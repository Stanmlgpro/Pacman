//
// Created by stan1 on 08/11/2025.
//

#include "SFMLGhostView.h"
#include "entities/Entity.h"
#include <iostream>
#include <utility>
namespace views {
SFMLGhostView::SFMLGhostView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                             std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window,
                             std::shared_ptr<Camera> camera)
    : SFMLView(texture, std::move(atlas), std::move(entity), window, std::move(camera)) {
    // set the variables timers, etc...
    animation_bool = true;
    animation_speed = 0.1f;
    animation_counter = 0;
    animation_bool_feared = true;
    animation_speed_feared = 0.4f;
    animation_counter_feared = 0;
}

void SFMLGhostView::Update(const float dt) {
    // update the animation counter
    animation_counter += dt;
    // check if we need to swap our boolean value
    if (animation_counter > animation_speed) {
        animation_bool = not animation_bool;
        animation_counter = 0;
    }
    // if we are not feared reset the feared counter
    if (!entity.lock()->getFeared()) {
        animation_counter_feared = 0;
        animation_bool_feared = false;
    } else {
        // otherwise update it as well
        animation_counter_feared += dt;
        // and swap if needed as well
        if (animation_counter_feared > animation_speed_feared) {
            animation_bool_feared = not animation_bool_feared;
            animation_counter_feared = 0;
        }
    }
    // find the correct sprite based on the newly found values
    FindSprite();
}

void SFMLGhostView::Draw() {
    // find the correct sprite
    FindSprite();
    // check for existence of the reference to the entity
    const auto e = entity.lock();
    if (!e)
        return;

    // set the correct screen position, scale using the camera class
    const auto screensize = camera->getSpritePixelSize();
    const auto screenpos = camera->worldToPixel(e->getPosition().x, e->getPosition().y);
    sprite.setScale(screensize.x / 16.f, screensize.y / 16.f);
    sprite.setPosition(screenpos.x, screenpos.y);

    window.draw(sprite); // draw the sprite onto the screen
}
} // namespace views