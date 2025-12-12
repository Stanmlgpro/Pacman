//
// Created by stan1 on 12/12/2025.
//

#ifndef SFMLWORLDVIEW_H
#define SFMLWORLDVIEW_H
#include "SFMLView.h"

namespace views {
    class SFMLWorldView : public SFMLView {
    public:
        SFMLWorldView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, sf::RenderWindow& window, std::shared_ptr<Camera> camera);

        void Update(float dt) override;
        void FindSprite() override;
        void setLives(int lives) override;
        void setScore(int score) override;

        void Draw() override;
    private:
        sf::Font font;
        sf::Text scoreText;
        sf::Text livesText;
        int score;
        int lives;
    };
}

#endif //SFMLWORLDVIEW_H
