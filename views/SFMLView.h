//
// Created by stan1 on 06/11/2025.
//

#ifndef SFMLVIEW_H
#define SFMLVIEW_H
#include "View.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <factory/SpriteAtlas.h>
#include <string>
namespace views {
class SFMLView : public View {
public:
    SFMLView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
             std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);

    void Update(float dt) override = 0;
    virtual void FindSprite() = 0;

    void Draw() override = 0;

protected:
    sf::Sprite sprite;
    sf::Texture texture;
    std::shared_ptr<sprites::SpriteAtlas> atlas;
    sf::RenderWindow& window;
};
} // namespace views

#endif // SFMLVIEW_H
