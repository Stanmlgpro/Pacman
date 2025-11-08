//
// Created by stan1 on 08/11/2025.
//

#ifndef SFMLLOCKEDGHOSTVIEW_H
#define SFMLLOCKEDGHOSTVIEW_H
#include "SFMLGhostView.h"


class SFMLLockedGhostView : public SFMLGhostView {
public:
    SFMLLockedGhostView(const sf::Texture& texture, std::weak_ptr<Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);

    void FindSprite() override;
};

#endif //SFMLLOCKEDGHOSTVIEW_H
