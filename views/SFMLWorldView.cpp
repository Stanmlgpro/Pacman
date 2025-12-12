//
// Created by stan1 on 12/12/2025.
//

#include "SFMLWorldView.h"
#include "World.h"
#include <iostream>

namespace views {
    SFMLWorldView::SFMLWorldView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, sf::RenderWindow& window, std::shared_ptr<Camera> camera) : SFMLView(texture, atlas, std::weak_ptr<entities::Entity>(), window, camera) {
        FindSprite();

#ifdef _WIN32
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
#else
        font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
#endif

        scoreText.setFont(font);
        //scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 10);

        livesText.setFont(font);
        //livesText.setCharacterSize(20);
        livesText.setFillColor(sf::Color::Yellow);
    }

    void SFMLWorldView::Update(float dt) {
        scoreText.setString("Score: " + std::to_string(score));
        livesText.setString("Lives: " + std::to_string(lives));
    }

    void SFMLWorldView::FindSprite() {
        sprite.setTextureRect(atlas->get(sprites::Sprite_ID::BLUE_100));
    }

    void SFMLWorldView::Draw() {
        scoreText.setPosition(-1, -1);
        livesText.setPosition(-1, 0);

        auto screensize = camera->getSpritePixelSize();
        auto screenpos = camera->worldToPixel(-0.98, -0.98);
        scoreText.setScale(screensize.x / 64.f, screensize.y / 64.f);
        scoreText.setPosition(screenpos.x, screenpos.y);
        screenpos = camera->worldToPixel(-0.98, 0.84);
        livesText.setScale(screensize.x / 64.f, screensize.y / 64.f);
        livesText.setPosition(screenpos.x, screenpos.y);

        window.draw(scoreText);
        window.draw(livesText);
    }
    void SFMLWorldView::setLives(int lives) {
        this->lives = lives;
    }
    void SFMLWorldView::setScore(int score) {
        this->score = score;
    }
}