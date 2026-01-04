//
// Created by stan1 on 12/12/2025.
//

#include "SFMLFruitView.h"

#include "entities/Entity.h"
#include <utility>

namespace views {
SFMLFruitView::SFMLFruitView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                             std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window,
                             std::shared_ptr<Camera> camera)
    : SFMLView(texture, std::move(atlas), std::move(entity), window, std::move(camera)) {
    // Create an SFMLView object
    // set the correct Origin
    sprite.setOrigin(8.f, 8.f);
}

void SFMLFruitView::Update(float dt) {}

void SFMLFruitView::Draw() {
    // lock the weak pointer and only draw if the reference exists
    const auto e = entity.lock();
    if (!e)
        return;

    // set the correct position and scale using the camera class
    const auto screensize = camera->getSpritePixelSize();
    const auto screenpos = camera->worldToPixel(e->getPosition().x, e->getPosition().y);

    sprite.setScale(screensize.x / 16.f, screensize.y / 16.f);
    sprite.setPosition(screenpos.x, screenpos.y);

    window.draw(sprite); // draw the sprite onto the window
}

SFMLCherryView::SFMLCherryView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                               std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window,
                               std::shared_ptr<Camera> camera)
    : SFMLFruitView(texture, std::move(atlas), std::move(entity), window, std::move(camera)) {
    // create an SFMLFruitView object and find the correct sprite
    FindSprite();
}
// report the correct SpritID to the atlas based on the class to find the correct sprite
void SFMLCherryView::FindSprite() { sprite.setTextureRect(atlas->get(sprites::Sprite_ID::FRUIT_CHERRY)); }

SFMLStrawberryView::SFMLStrawberryView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                                       std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window,
                                       std::shared_ptr<Camera> camera)
    // create an SFMLFruitView object and find the correct sprite
    : SFMLFruitView(texture, std::move(atlas), std::move(entity), window, std::move(camera)) {
    FindSprite();
}
// report the correct SpritID to the atlas based on the class to find the correct sprite
void SFMLStrawberryView::FindSprite() { sprite.setTextureRect(atlas->get(sprites::Sprite_ID::FRUIT_STRAWBERRY)); }

SFMLMelonView::SFMLMelonView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                             std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window,
                             std::shared_ptr<Camera> camera)
    // create an SFMLFruitView object and find the correct sprite
    : SFMLFruitView(texture, std::move(atlas), std::move(entity), window, std::move(camera)) {
    FindSprite();
}
// report the correct SpritID to the atlas based on the class to find the correct sprite
void SFMLMelonView::FindSprite() { sprite.setTextureRect(atlas->get(sprites::Sprite_ID::FRUIT_MELON)); }

SFMLAppleView::SFMLAppleView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                             std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window,
                             std::shared_ptr<Camera> camera)
    // create an SFMLFruitView object and find the correct sprite
    : SFMLFruitView(texture, std::move(atlas), std::move(entity), window, std::move(camera)) {
    FindSprite();
}
// report the correct SpritID to the atlas based on the class to find the correct sprite
void SFMLAppleView::FindSprite() { sprite.setTextureRect(atlas->get(sprites::Sprite_ID::FRUIT_APPLE)); }

SFMLOrangeView::SFMLOrangeView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                               std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window,
                               std::shared_ptr<Camera> camera)
    // create an SFMLFruitView object and find the correct sprite
    : SFMLFruitView(texture, std::move(atlas), std::move(entity), window, std::move(camera)) {
    FindSprite();
}
void SFMLOrangeView::FindSprite() { sprite.setTextureRect(atlas->get(sprites::Sprite_ID::FRUIT_ORANGE)); }

SFMLGalaxianView::SFMLGalaxianView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                                   std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window,
                                   std::shared_ptr<Camera> camera)
    // create an SFMLFruitView object and find the correct sprite
    : SFMLFruitView(texture, std::move(atlas), std::move(entity), window, std::move(camera)) {
    FindSprite();
}
// report the correct SpritID to the atlas based on the class to find the correct sprite
void SFMLGalaxianView::FindSprite() { sprite.setTextureRect(atlas->get(sprites::Sprite_ID::FRUIT_GALAXIAN)); }

SFMLBellView::SFMLBellView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                           std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window,
                           std::shared_ptr<Camera> camera)
    // create an SFMLFruitView object and find the correct sprite
    : SFMLFruitView(texture, std::move(atlas), std::move(entity), window, std::move(camera)) {
    FindSprite();
}
// report the correct SpritID to the atlas based on the class to find the correct sprite
void SFMLBellView::FindSprite() { sprite.setTextureRect(atlas->get(sprites::Sprite_ID::FRUIT_BELL)); }

SFMLKeyView::SFMLKeyView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                         std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window,
                         std::shared_ptr<Camera> camera)
    // create an SFMLFruitView object and find the correct sprite
    : SFMLFruitView(texture, std::move(atlas), std::move(entity), window, std::move(camera)) {
    FindSprite();
}
// report the correct SpritID to the atlas based on the class to find the correct sprite
void SFMLKeyView::FindSprite() { sprite.setTextureRect(atlas->get(sprites::Sprite_ID::FRUIT_KEY)); }
} // namespace views