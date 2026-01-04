//
// Created by stan1 on 06/11/2025.
//

#include "SFMLWallView.h"

#include <utility>
#include "entities/Entity.h"
namespace views {
SFMLWallView::SFMLWallView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera)
    : SFMLView(texture, std::move(atlas), std::move(entity), window, std::move(camera)) { // create an SFMLView object
    rect.setFillColor(sf::Color(0, 0, 180));             // set the rectangle color
}

void SFMLWallView::Update(float dt) {}

void SFMLWallView::Draw() {
    // check for existence of the reference to the entity
    const auto e = entity.lock();
    if (!e)
        return;

    // set the correct screen position, scale using the camera class
    const auto screensize = camera->getSpritePixelSize();
    const auto screenpos = camera->worldToPixel(e->getPosition().x, e->getPosition().y);

    // Update size, origin, and position together each frame
    rect.setSize(sf::Vector2f(screensize.x, screensize.y));
    rect.setOrigin(screensize.x / 2.f,
                   screensize.y / 2.f); // Center origin based on current size
    rect.setPosition(screenpos.x, screenpos.y);

    window.draw(rect); // draw the rectangle onto the screen
}
} // namespace views
