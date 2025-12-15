//
// Created by stan1 on 08/11/2025.
//

#include "SFMLOrbView.h"
#include "entities/Entity.h"

namespace views {
SFMLOrbView::SFMLOrbView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                         std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window,
                         std::shared_ptr<Camera> camera)
    : SFMLView(texture, atlas, entity, window, camera) {
    FindSprite();
    sprite.setOrigin(0.f, 0.f);
}

void SFMLOrbView::Update(float dt) {}

void SFMLOrbView::FindSprite() { sprite.setTextureRect(atlas->get(sprites::Sprite_ID::ORB_SMALL)); }

void SFMLOrbView::Draw() {
    auto e = entity.lock();
    if (!e)
        return;

    auto screensize = camera->getSpritePixelSize();
    auto screenpos = camera->worldToPixel(e->getPosition().x, e->getPosition().y);

    sprite.setScale(screensize.x / 16.f, screensize.y / 16.f);
    sprite.setPosition(screenpos.x, screenpos.y);

    window.draw(sprite);
}
} // namespace views