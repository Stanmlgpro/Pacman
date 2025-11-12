//
// Created by stan1 on 08/11/2025.
//

#ifndef SFMLORBVIEW_H
#define SFMLORBVIEW_H
#include <views/SFMLView.h>


class SFMLOrbView : public SFMLView {
public:
    SFMLOrbView(const sf::Texture& texture, std::weak_ptr<Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);

    void Update(float dt) override;
    void FindSprite();

    void Draw() override;
private:
    sf::Sprite sprite;
    sf::CircleShape circ;
};



#endif //SFMLORBVIEW_H
