//
// Created by stan1 on 12/12/2025.
//

#ifndef SFMLWORLDVIEW_H
#define SFMLWORLDVIEW_H
#include <entities/Entity.h>
#include "SFMLView.h"

namespace views {
    struct ScoreEntry {
        Position position;
        sprites::Sprite_ID spriteID;
        float lifetime;
        sf::Sprite sprite;
        bool operator==(const ScoreEntry& other) const;
        void Draw(sf::RenderWindow& window) const;
        void setScale(float scaleX, float scaleY);
        void setPosition(float x, float y);
        void Update(float dt);
    };

    class SFMLWorldView : public SFMLView {
    public:
        SFMLWorldView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, sf::RenderWindow& window, std::shared_ptr<Camera> camera);

        void Update(float dt) override;
        void FindSprite() override;
        void addScoreEntry(sprites::Sprite_ID ID, float lifetime, Position position);

        void setLives(int lives) override;
        void setScore(int score) override;
        void ItemEaten(sprites::Sprite_ID ID, Position position) override;

        void Draw() override;
    private:
        sf::Font font;
        sf::Text scoreText;
        sf::Text livesText;
        int score;
        int lives;
        std::vector<ScoreEntry> scoreEntries;
        std::vector<ScoreEntry> toRemove;
    };
}

#endif //SFMLWORLDVIEW_H
