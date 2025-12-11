//
// Created by stan1 on 09/11/2025.
//

#include "SFMLPredictGhost1View.h"
#include "entities/Entity.h"
namespace views {
    SFMLPredictGhost1View::SFMLPredictGhost1View(const sf::Texture& texture, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera) : SFMLGhostView(texture, entity, window, camera){}

    void SFMLPredictGhost1View::FindSprite() {
        auto e = entity.lock();
        if (!e) return;
        int dirX = e->getDirection()[0];
        int dirY = e->getDirection()[1];

        sf::IntRect rect;
        if (e->getFeared() and e->getFearCheck() < 4.f) {
            rect = animation_bool ? sf::IntRect(128, 64, 16, 16) : sf::IntRect(144, 64, 16, 16);
        }
        else if (e->getFeared()) {
            if (animation_bool_feared) {
                rect = animation_bool ? sf::IntRect(128, 64, 16, 16) : sf::IntRect(144, 64, 16, 16);
            }
            else {
                rect = animation_bool ? sf::IntRect(160, 64, 16, 16) : sf::IntRect(176, 64, 16, 16);
            }
        }
        else if (dirX == -1 && dirY == 0) {
            if (e->getDying()) rect = sf::IntRect(144, 80, 16, 16);
            else rect = animation_bool ? sf::IntRect(32, 80, 16, 16) : sf::IntRect(48, 80, 16, 16);
        }
        else if (dirX == 0 && dirY == 1) {
            if (e->getDying()) rect = sf::IntRect(176, 80, 16, 16);
            else rect = animation_bool ? sf::IntRect(96, 80, 16, 16) : sf::IntRect(112, 80, 16, 16);
        }
        else if (dirX == 0 && dirY == -1) {
            if (e->getDying()) rect = sf::IntRect(160, 80, 16, 16);
            else rect = animation_bool ? sf::IntRect(64, 80, 16, 16) : sf::IntRect(80, 80, 16, 16);
        }
        else if (dirX == 1 && dirY == 0) {
            if (e->getDying()) rect = sf::IntRect(128, 80, 16, 16);
            else rect = animation_bool ? sf::IntRect(0, 80, 16, 16) : sf::IntRect(16, 80, 16, 16);
        }
        else {
            if (e->getDying()) rect = sf::IntRect(128, 80, 16, 16);
            else rect = animation_bool ? sf::IntRect(0, 80, 16, 16) : sf::IntRect(16, 80, 16, 16);
        }
        sprite.setTextureRect(rect);
    }
}