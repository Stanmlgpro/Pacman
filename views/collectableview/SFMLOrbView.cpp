//
// Created by stan1 on 08/11/2025.
//

#include "SFMLOrbView.h"
#include "entities/Entity.h"
namespace views {
    SFMLOrbView::SFMLOrbView(const sf::Texture& texture, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera) : SFMLView(texture, entity, window, camera) {
        circ.setFillColor(sf::Color::Yellow);
    }

    void SFMLOrbView::Update(float dt) {}

    void SFMLOrbView::Draw() {
        auto e = entity.lock();
        if (!e) return;

        auto screensize = camera->getSpritePixelSize();
        auto screenpos = camera->worldToPixel(e->getPosition().x, e->getPosition().y);


        screensize.x /= 10.f;
        screensize.y /= 10.f;
        circ.setRadius(screensize.x);
        circ.setOrigin(screensize.x / 2.f, screensize.y / 2.f);
        circ.setPosition(screenpos.x, screenpos.y);

        window.draw(circ);
    }
}