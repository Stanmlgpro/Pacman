//
// Created by stan1 on 08/11/2025.
//

#ifndef SFMLGHOSTVIEW_H
#define SFMLGHOSTVIEW_H
#include "views/SFMLView.h"


class SFMLGhostView : public SFMLView {
public:
    SFMLGhostView(const sf::Texture& texture, std::weak_ptr<Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);

    void Update(float dt) override;
    void FindSprite();

    void Draw() override;
private:
    sf::Sprite sprite;
    bool animation_bool;
    float animation_speed;
    float animation_counter;
};



#endif //SFMLGHOSTVIEW_H
