//
// Created by stan1 on 06/11/2025.
//

#ifndef SFMLWALLVIEW_H
#define SFMLWALLVIEW_H
#include <views/SFMLView.h>


class SFMLWallView : public SFMLView {
public:
    SFMLWallView(const sf::Texture& texture, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);

    void Update(float dt) override;

    void Draw() override;
private:
    sf::Sprite sprite;
    sf::RectangleShape rect;
};



#endif //SFMLWALLVIEW_H
