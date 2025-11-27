//
// Created by stan1 on 09/11/2025.
//

#ifndef SFMLCHASEGHOSTVIEW_H
#define SFMLCHASEGHOSTVIEW_H
#include "SFMLGhostView.h"


class SFMLChaseGhostView : public SFMLGhostView {
public:
    SFMLChaseGhostView(const sf::Texture& texture, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);

    void FindSprite() override;
};



#endif //SFMLCHASEGHOSTVIEW_H
