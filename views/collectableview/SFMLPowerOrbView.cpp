//
// Created by stan1 on 11/12/2025.
//

#include "SFMLPowerOrbView.h"
#include "entities/Entity.h"
#include <iostream>
namespace views {
SFMLPowerOrbView::SFMLPowerOrbView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                                   std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window,
                                   std::shared_ptr<Camera> camera)
    : SFMLView(texture, atlas, entity, window, camera) {
    // Create an SFMLView object
    // Find the correct sprite
    FindSprite();
    // set the correct Origin
    sprite.setOrigin(4.f, 4.f);
}

void SFMLPowerOrbView::Update(float dt) {}
// report the correct SpritID to the atlas based on the class to find the correct sprite
void SFMLPowerOrbView::FindSprite() { sprite.setTextureRect(atlas->get(sprites::Sprite_ID::ORB_BIG)); }

void SFMLPowerOrbView::Draw() {
    // lock the weak pointer and only draw if the reference exists
    auto e = entity.lock();
    if (!e)
        return;

    // set the correct position and scale using the camera class
    auto screensize = camera->getSpritePixelSize();
    auto screenpos = camera->worldToPixel(e->getPosition().x, e->getPosition().y);

    sprite.setScale(screensize.x / 16.f, screensize.y / 16.f);
    sprite.setPosition(screenpos.x, screenpos.y);
    sprite.setOrigin(4.f, 4.f);

    window.draw(sprite); // draw the sprite onto the window
}
} // namespace views