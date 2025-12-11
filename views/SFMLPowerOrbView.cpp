//
// Created by stan1 on 11/12/2025.
//

#include "SFMLPowerOrbView.h"
#include "entities/Entity.h"
namespace views {
    SFMLPowerOrbView::SFMLPowerOrbView(const sf::Texture& texture, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera) : SFMLView(texture, entity, window, camera) {
        sprite.setTexture(texture);
        sprite.setScale(1.f, 1.f);
        sprite.setOrigin(8.f,8.f);

        FindSprite();
    }

    void SFMLPowerOrbView::Update(float dt) {}

    void SFMLPowerOrbView::FindSprite() {
        sprite.setTextureRect(sf::IntRect(16 * random.get(0, 4), 128, 16, 16));
    }

    void SFMLPowerOrbView::Draw() {
        auto e = entity.lock();
        if (!e) return;

        auto screensize = camera->getSpritePixelSize();
        auto screenpos = camera->worldToPixel(e->getPosition().x, e->getPosition().y);

        sprite.setScale(screensize.x / 16.f, screensize.y / 16.f);
        sprite.setPosition(screenpos.x, screenpos.y);

        window.draw(sprite);
    }
}