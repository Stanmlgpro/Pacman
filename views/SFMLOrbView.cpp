//
// Created by stan1 on 08/11/2025.
//

#include "SFMLOrbView.h"
#include "entities/Entity.h"

SFMLOrbView::SFMLOrbView(const sf::Texture& texture, std::weak_ptr<Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera) : SFMLView(texture, entity, window, camera) {
    auto e = entity.lock();
    if (e->isBig()) circ.setFillColor(sf::Color::Magenta);
    else circ.setFillColor(sf::Color::Yellow);

}

void SFMLOrbView::Update(float dt) {}

void SFMLOrbView::Draw() {
    auto e = entity.lock();
    if (!e) return;

    auto screensize = camera->getSpritePixelSize();
    auto screenpos = camera->worldToPixel(e->getPosition().x, e->getPosition().y);

    screensize.x /= 10.f;
    screensize.y /= 10.f;
    // Update size, origin, and position together each frame
    circ.setRadius(screensize.x);
    if (e->isBig()) circ.setRadius(screensize.x * 2.f);
    circ.setOrigin(screensize.x / 2.f, screensize.y / 2.f);  // Center origin based on current size
    if (e->isBig()) circ.setOrigin(screensize.x / 2.f, screensize.y / 2.f);
    circ.setPosition(screenpos.x, screenpos.y);

    window.draw(circ);
}