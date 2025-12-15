//
// Created by stan1 on 06/11/2025.
//
#include "SFMLPacmanView.h"
#include "entities/Entity.h"
#include <iostream>
namespace views {
SFMLPacmanView::SFMLPacmanView(const sf::Texture &texture,
                               std::shared_ptr<sprites::SpriteAtlas> atlas,
                               std::weak_ptr<entities::Entity> entity,
                               sf::RenderWindow &window,
                               std::shared_ptr<Camera> camera)
    : SFMLView(texture, atlas, entity, window, camera) {
  sprite.setScale(1.f, 1.f);
  sprite.setOrigin(8.f, 8.f);
  open = true;
  animation_speed = 0.1f;
  animation_counter = 0;
}

void SFMLPacmanView::Update(float dt) {
  animation_counter += dt;
  if (animation_counter > animation_speed) {
    open = not open;
    animation_counter = 0;
  }
  if (entity.lock()->getDying())
    current_dying_frame += dt * 10;
  else
    current_dying_frame = 0;
  FindSprite();
}

void SFMLPacmanView::FindSprite() {
  auto e = entity.lock();
  if (!e)
    return;

  int dirX = e->getDirection()[0];
  int dirY = e->getDirection()[1];
  bool dying = e->getDying();
  sf::IntRect rect;

  if (!dying)
    current_dying_frame = 0;
  if (dying) {
    switch (static_cast<int>(std::floor(current_dying_frame))) {
    case 0:
      rect = atlas->get(sprites::Sprite_ID::PACMAN_DYING_1);
      break;
    case 1:
      rect = atlas->get(sprites::Sprite_ID::PACMAN_DYING_2);
      break;
    case 2:
      rect = atlas->get(sprites::Sprite_ID::PACMAN_DYING_3);
      break;
    case 3:
      rect = atlas->get(sprites::Sprite_ID::PACMAN_DYING_4);
      break;
    case 4:
      rect = atlas->get(sprites::Sprite_ID::PACMAN_DYING_5);
      break;
    case 5:
      rect = atlas->get(sprites::Sprite_ID::PACMAN_DYING_6);
      break;
    case 6:
      rect = atlas->get(sprites::Sprite_ID::PACMAN_DYING_7);
      break;
    case 7:
      rect = atlas->get(sprites::Sprite_ID::PACMAN_DYING_8);
      break;
    case 8:
      rect = atlas->get(sprites::Sprite_ID::PACMAN_DYING_9);
      break;
    case 9:
      rect = atlas->get(sprites::Sprite_ID::PACMAN_DYING_10);
      break;
    case 10:
      rect = atlas->get(sprites::Sprite_ID::PACMAN_DYING_11);
      break;
    case 11:
      rect = atlas->get(sprites::Sprite_ID::PACMAN_DYING_12);
      break;
    default:
      rect = atlas->get(sprites::Sprite_ID::PACMAN_DYING_12);
      break;
    }
  } else if (dirX == 0 && dirY == -1) {
    rect = open ? atlas->get(sprites::Sprite_ID::PACMAN_UP_1)
                : atlas->get(sprites::Sprite_ID::PACMAN_UP_2);
  } else if (dirX == 0 && dirY == 1) {
    rect = open ? atlas->get(sprites::Sprite_ID::PACMAN_DOWN_1)
                : atlas->get(sprites::Sprite_ID::PACMAN_DOWN_2);
  } else if (dirX == -1 && dirY == 0) {
    rect = open ? atlas->get(sprites::Sprite_ID::PACMAN_LEFT_1)
                : atlas->get(sprites::Sprite_ID::PACMAN_LEFT_2);
  } else if (dirX == 1 && dirY == 0) {
    rect = open ? atlas->get(sprites::Sprite_ID::PACMAN_RIGHT_1)
                : atlas->get(sprites::Sprite_ID::PACMAN_RIGHT_2);
  } else {
    rect = atlas->get(sprites::Sprite_ID::PACMAN_IDLE);
  }

  sprite.setTextureRect(rect);
}

void SFMLPacmanView::Draw() {
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