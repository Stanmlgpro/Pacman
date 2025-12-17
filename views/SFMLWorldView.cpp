//
// Created by stan1 on 12/12/2025.
//

#include "SFMLWorldView.h"
#include "World.h"
#include <iostream>

namespace views {
bool ScoreEntry::operator==(const ScoreEntry& other) const {
    return position.x == other.position.x && position.y == other.position.y && spriteID == other.spriteID;
}
void ScoreEntry::Draw(sf::RenderWindow& window) const { window.draw(sprite); }
void ScoreEntry::setScale(float scaleX, float scaleY) { sprite.setScale(scaleX, scaleY); }
void ScoreEntry::setPosition(float x, float y) { sprite.setPosition(x, y); }
void ScoreEntry::Update(float dt) { lifetime -= dt; }

SFMLWorldView::SFMLWorldView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas,
                             sf::RenderWindow& window, std::shared_ptr<Camera> camera)
    : SFMLView(texture, atlas, std::weak_ptr<entities::Entity>(), window, camera), score(0), lives(3) {
    FindSprite();
    sprite.setTexture(texture);
    sprite.setScale(1.f, 1.f);
    sprite.setOrigin(0.f, 0.f);

    life1 = sprite;
    life2 = sprite;
    life3 = sprite;

#ifdef _WIN32
    font.loadFromFile("C:/Windows/Fonts/lucon.ttf"); // Lucida Console
#else
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf");
#endif

    scoreText.setFont(font);
    scoreText.setLetterSpacing(1.1f);
    scoreText.setFillColor(sf::Color::Yellow);
}

void SFMLWorldView::Update(float dt) {
    scoreText.setString("Score:" + std::to_string(score));
    std::for_each(scoreEntries.begin(), scoreEntries.end(), [this, dt](ScoreEntry& entry) {
        entry.Update(dt);
        if (entry.lifetime <= 0.f) {
            toRemove.push_back(entry);
        }
    });
    for (const auto& entry : toRemove) {
        scoreEntries.erase(std::remove_if(scoreEntries.begin(), scoreEntries.end(),
                                          [&entry](const ScoreEntry& e) { return e == entry; }),
                           scoreEntries.end());
    }
    toRemove.clear();
}

void SFMLWorldView::FindSprite() { sprite.setTextureRect(atlas->get(sprites::Sprite_ID::PACMAN_RIGHT_2)); }

void SFMLWorldView::Draw() {
    auto screensize = camera->getSpritePixelSize();
    auto screenpos = camera->worldToPixel(0.4, 1.2);
    scoreText.setScale(screensize.x / 32.f, screensize.y / 32.f);
    scoreText.setPosition(screenpos.x, screenpos.y);
    window.draw(scoreText);

    screenpos = camera->worldToPixel(-1, 1);
    life1.setPosition(screenpos.x, screenpos.y);
    life1.setScale(screensize.x / 16.f, screensize.y / 16.f);
    screenpos = camera->worldToPixel(-0.9, 1);
    life2.setPosition(screenpos.x, screenpos.y);
    life2.setScale(screensize.x / 16.f, screensize.y / 16.f);
    screenpos = camera->worldToPixel(-0.8, 1);
    life3.setPosition(screenpos.x, screenpos.y);
    life3.setScale(screensize.x / 16.f, screensize.y / 16.f);

    if (lives > 0)
        window.draw(life1);
    if (lives > 1)
        window.draw(life2);
    if (lives > 2)
        window.draw(life3);

    for (auto& entry : scoreEntries) {
        auto screenpos = camera->worldToPixel(entry.position.x, entry.position.y);
        entry.setScale(screensize.x / 16.f, screensize.y / 16.f);
        entry.setPosition(screenpos.x, screenpos.y);
        entry.Draw(window);
    }
}
void SFMLWorldView::setLives(int lives) { this->lives = lives; }
void SFMLWorldView::setScore(int score) { this->score = score; }
void SFMLWorldView::addScoreEntry(sprites::Sprite_ID ID, float lifetime, Position position) {
    ScoreEntry entry;
    entry.spriteID = ID;
    entry.lifetime = lifetime;
    entry.position = position;
    entry.sprite.setTexture(texture);
    entry.sprite.setTextureRect(atlas->get(ID));
    entry.setScale(1.f, 1.f);
    entry.setPosition(100.f, 100.f);
    scoreEntries.push_back(entry);
}
void SFMLWorldView::ItemEaten(sprites::Sprite_ID ID, Position position) {
    switch (ID) {

    case sprites::Sprite_ID::ORB_BIG:
    case sprites::Sprite_ID::FRUIT_CHERRY:
        addScoreEntry(sprites::Sprite_ID::BLUE_100, 2.0f, position);
        break;
    case sprites::Sprite_ID::FRUIT_STRAWBERRY:
        addScoreEntry(sprites::Sprite_ID::BLUE_300, 1.0f, position);
        break;
    case sprites::Sprite_ID::FRUIT_ORANGE:
        addScoreEntry(sprites::Sprite_ID::BLUE_500, 1.0f, position);
        break;
    case sprites::Sprite_ID::FRUIT_APPLE:
        addScoreEntry(sprites::Sprite_ID::BLUE_700, 1.0f, position);
        break;
    case sprites::Sprite_ID::FRUIT_MELON:
        addScoreEntry(sprites::Sprite_ID::BLUE_1000, 1.0f, position);
        break;
    case sprites::Sprite_ID::FRUIT_GALAXIAN:
        addScoreEntry(sprites::Sprite_ID::BLUE_2000, 1.0f, position);
        break;
    case sprites::Sprite_ID::FRUIT_BELL:
        addScoreEntry(sprites::Sprite_ID::BLUE_3000, 1.0f, position);
        break;
    case sprites::Sprite_ID::FRUIT_KEY:
        addScoreEntry(sprites::Sprite_ID::BLUE_5000, 1.0f, position);
        break;
    case sprites::Sprite_ID::GHOST_EYES_RIGHT:
        addScoreEntry(sprites::Sprite_ID::WHITE_200, 1.0f, position);
        break;
    case sprites::Sprite_ID::GHOST_EYES_LEFT:
        addScoreEntry(sprites::Sprite_ID::WHITE_400, 1.0f, position);
        break;
    case sprites::Sprite_ID::GHOST_EYES_UP:
        addScoreEntry(sprites::Sprite_ID::WHITE_800, 1.0f, position);
        break;
    case sprites::Sprite_ID::GHOST_EYES_DOWN:
        addScoreEntry(sprites::Sprite_ID::WHITE_1600, 1.0f, position);
        break;
    default:
        break;
    }
}

} // namespace views