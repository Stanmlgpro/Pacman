//
// Created by stan1 on 06/11/2025.
//

#ifndef SFMLPACMANVIEW_H
#define SFMLPACMANVIEW_H
#include "SFMLView.h"

namespace views {
    class SFMLPacmanView : public SFMLView {
    public:
        SFMLPacmanView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);

        void Update(float dt) override;
        void FindSprite() override;

        void Draw() override;
    private:
        bool open;
        float animation_speed;
        float animation_counter;
        float current_dying_frame = 0;
    };
}


#endif //SFMLPACMANVIEW_H
