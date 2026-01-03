//
// Created by stan1 on 08/11/2025.
//

#include "SFMLLockedGhostView.h"
#include "entities/Entity.h"
namespace views {
SFMLLockedGhostView::SFMLLockedGhostView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                                         std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window,
                                         std::shared_ptr<Camera> camera)
    : SFMLGhostView(texture, atlas, entity, window, camera) {} // create an SFMLGhostView object

void SFMLLockedGhostView::FindSprite() {
    // check for the existence of the reference
    auto e = entity.lock();
    if (!e)
        return;
    // and on existence pick the correct SpritID needed for the current state of the ghost and report that to the atlas
    // to get the correct rectangle
    int dirX = e->getDirection()[0];
    int dirY = e->getDirection()[1];

    sf::IntRect rect;
    if (e->getFeared() and e->getFearCheck() < 4.f) {
        rect = animation_bool ? atlas->get(sprites::Sprite_ID::GHOST_FEAR_BLUE_1)
                              : atlas->get(sprites::Sprite_ID::GHOST_FEAR_BLUE_2);
    } else if (e->getFeared()) {
        if (animation_bool_feared) {
            rect = animation_bool ? atlas->get(sprites::Sprite_ID::GHOST_FEAR_BLUE_1)
                                  : atlas->get(sprites::Sprite_ID::GHOST_FEAR_BLUE_2);
        } else {
            rect = animation_bool ? atlas->get(sprites::Sprite_ID::GHOST_FEAR_FLASH_1)
                                  : atlas->get(sprites::Sprite_ID::GHOST_FEAR_FLASH_2);
        }
    } else if (dirX == -1 && dirY == 0) {
        if (e->getDying())
            rect = atlas->get(sprites::Sprite_ID::GHOST_EYES_LEFT);
        else
            rect = animation_bool ? atlas->get(sprites::Sprite_ID::GHOST_YELLOW_LEFT_1)
                                  : atlas->get(sprites::Sprite_ID::GHOST_YELLOW_LEFT_2);
    } else if (dirX == 0 && dirY == 1) {
        if (e->getDying())
            rect = atlas->get(sprites::Sprite_ID::GHOST_EYES_DOWN);
        else
            rect = animation_bool ? atlas->get(sprites::Sprite_ID::GHOST_YELLOW_DOWN_1)
                                  : atlas->get(sprites::Sprite_ID::GHOST_YELLOW_DOWN_2);
    } else if (dirX == 0 && dirY == -1) {
        if (e->getDying())
            rect = atlas->get(sprites::Sprite_ID::GHOST_EYES_UP);
        else
            rect = animation_bool ? atlas->get(sprites::Sprite_ID::GHOST_YELLOW_UP_1)
                                  : atlas->get(sprites::Sprite_ID::GHOST_YELLOW_UP_2);
    } else if (dirX == 1 && dirY == 0) {
        if (e->getDying())
            rect = atlas->get(sprites::Sprite_ID::GHOST_EYES_RIGHT);
        else
            rect = animation_bool ? atlas->get(sprites::Sprite_ID::GHOST_YELLOW_RIGHT_1)
                                  : atlas->get(sprites::Sprite_ID::GHOST_YELLOW_RIGHT_2);
    } else {
        if (e->getDying())
            rect = atlas->get(sprites::Sprite_ID::GHOST_EYES_RIGHT);
        else
            rect = animation_bool ? atlas->get(sprites::Sprite_ID::GHOST_YELLOW_RIGHT_1)
                                  : atlas->get(sprites::Sprite_ID::GHOST_YELLOW_RIGHT_2);
    }
    sprite.setTextureRect(rect);
}
} // namespace views