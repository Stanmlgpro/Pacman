//
// Created by stan1 on 12/12/2025.
//

#include "SFMLFruitView.h"
#include "entities/Entity.h"

namespace views {
    SFMLFruitView::SFMLFruitView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera) : SFMLView(texture, atlas, entity, window, camera) {
        sprite.setOrigin(8.f, 8.f);
    }

    void SFMLFruitView::Update(float dt) {}

    void SFMLFruitView::Draw() {
        auto e = entity.lock();
        if (!e) return;

        auto screensize = camera->getSpritePixelSize();
        auto screenpos = camera->worldToPixel(e->getPosition().x, e->getPosition().y);

        sprite.setScale(screensize.x / 16.f, screensize.y / 16.f);
        sprite.setPosition(screenpos.x, screenpos.y);

        window.draw(sprite);
    }

    SFMLCherryView::SFMLCherryView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera)  : SFMLFruitView(texture, atlas, entity, window, camera) {
        FindSprite();
    }
    void SFMLCherryView::FindSprite() {
        sprite.setTextureRect(atlas->get(sprites::Sprite_ID::FRUIT_CHERRY));
    }

    SFMLStrawberryView::SFMLStrawberryView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera)  : SFMLFruitView(texture, atlas, entity, window, camera) {
        FindSprite();
    }
    void SFMLStrawberryView::FindSprite() {
        sprite.setTextureRect(atlas->get(sprites::Sprite_ID::FRUIT_STRAWBERRY));
    }

    SFMLMelonView::SFMLMelonView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera)  : SFMLFruitView(texture, atlas, entity, window, camera) {
        FindSprite();
    }
    void SFMLMelonView::FindSprite() {
        sprite.setTextureRect(atlas->get(sprites::Sprite_ID::FRUIT_MELON));
    }

    SFMLAppleView::SFMLAppleView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera)  : SFMLFruitView(texture, atlas, entity, window, camera) {
        FindSprite();
    }
    void SFMLAppleView::FindSprite() {
        sprite.setTextureRect(atlas->get(sprites::Sprite_ID::FRUIT_APPLE));
    }

    SFMLOrangeView::SFMLOrangeView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera)  : SFMLFruitView(texture, atlas, entity, window, camera) {
        FindSprite();
    }
    void SFMLOrangeView::FindSprite() {
        sprite.setTextureRect(atlas->get(sprites::Sprite_ID::FRUIT_ORANGE));
    }

    SFMLGalaxianView::SFMLGalaxianView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera)  : SFMLFruitView(texture, atlas, entity, window, camera) {
        FindSprite();
    }
    void SFMLGalaxianView::FindSprite() {
        sprite.setTextureRect(atlas->get(sprites::Sprite_ID::FRUIT_GALAXIAN));
    }

    SFMLBellView::SFMLBellView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera)  : SFMLFruitView(texture, atlas, entity, window, camera) {
        FindSprite();
    }
    void SFMLBellView::FindSprite() {
        sprite.setTextureRect(atlas->get(sprites::Sprite_ID::FRUIT_BELL));
    }

    SFMLKeyView::SFMLKeyView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera)  : SFMLFruitView(texture, atlas, entity, window, camera) {
        FindSprite();
    }
    void SFMLKeyView::FindSprite() {
        sprite.setTextureRect(atlas->get(sprites::Sprite_ID::FRUIT_KEY));
    }
}