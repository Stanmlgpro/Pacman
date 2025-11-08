//
// Created by stan1 on 09/11/2025.
//

#ifndef SFMLPREDICTGHOST2VIEW_H
#define SFMLPREDICTGHOST2VIEW_H
#include "SFMLGhostView.h"


class SFMLPredictGhost2View : public SFMLGhostView {
public:
    SFMLPredictGhost2View(const sf::Texture& texture, std::weak_ptr<Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);

    void FindSprite() override;
};



#endif //SFMLPREDICTGHOST2VIEW_H
