//
// Created by stan1 on 08/11/2025.
//

#ifndef SFMLLOCKEDGHOSTVIEW_H
#define SFMLLOCKEDGHOSTVIEW_H
#include "SFMLGhostView.h"

namespace views {
class SFMLLockedGhostView : public SFMLGhostView {
public:
    SFMLLockedGhostView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                        std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window,
                        std::shared_ptr<Camera> camera);

    void FindSprite() override;
};
} // namespace views
#endif // SFMLLOCKEDGHOSTVIEW_H
