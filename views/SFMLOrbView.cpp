//
// Created by stan1 on 08/11/2025.
//

#include "SFMLOrbView.h"
#include "entities/Entity.h"
namespace views {
    SFMLOrbView::SFMLOrbView(const sf::Texture& texture, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera) : SFMLView(texture, entity, window, camera) {
        auto e = entity.lock();
        if (!e->isBig()) {
            circ.setFillColor(sf::Color::Yellow);
            return;
        }
        sprite.setTexture(texture);
        sprite.setScale(1.f, 1.f);
        sprite.setOrigin(8.f,8.f);

        if (e->isBig()) FindSprite();
    }

    void SFMLOrbView::Update(float dt) {}

    void SFMLOrbView::FindSprite() {
        sprite.setTextureRect(sf::IntRect(16 * random.get(0, 4), 128, 16, 16));
    }

    void SFMLOrbView::Draw() {
        auto e = entity.lock();
        if (!e) return;

        auto screensize = camera->getSpritePixelSize();
        auto screenpos = camera->worldToPixel(e->getPosition().x, e->getPosition().y);


        if (!e->isBig()) {
            screensize.x /= 10.f;
            screensize.y /= 10.f;
            // Update size, origin, and position together each frame
            circ.setRadius(screensize.x);
            if (e->isBig()) circ.setRadius(screensize.x * 2.f);
            circ.setOrigin(screensize.x / 2.f, screensize.y / 2.f);  // Center origin based on current size
            if (e->isBig()) circ.setOrigin(screensize.x / 2.f, screensize.y / 2.f);
            circ.setPosition(screenpos.x, screenpos.y);

            window.draw(circ);
            return;
        }

        sprite.setScale(screensize.x / 16.f, screensize.y / 16.f);
        sprite.setPosition(screenpos.x, screenpos.y);

        window.draw(sprite);
    }
}