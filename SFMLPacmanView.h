//
// Created by stan1 on 06/11/2025.
//

#ifndef SFMLPACMANVIEW_H
#define SFMLPACMANVIEW_H
#include "SFMLView.h"


class SFMLPacmanView : public SFMLView {
public:
    SFMLPacmanView(const sf::Texture& texture, std::weak_ptr<Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);

    void Update(float dt) override;

    void Draw() override;
private:
    sf::Sprite sprite;
};



#endif //SFMLPACMANVIEW_H
