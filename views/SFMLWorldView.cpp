//
// Created by stan1 on 12/12/2025.
//

#include "SFMLWorldView.h"
#include "World.h"
#include <iostream>

namespace views {
bool ScoreEntry::operator==(const ScoreEntry& other) const {
    return position.x == other.position.x && position.y == other.position.y &&
           spriteID == other.spriteID; // simple copy constructor
}
void ScoreEntry::Draw(sf::RenderWindow& window) const { window.draw(sprite); }             // draw the entry
void ScoreEntry::setScale(const float scaleX, const float scaleY) { sprite.setScale(scaleX, scaleY); } // set the scale
void ScoreEntry::setPosition(const float x, const float y) { sprite.setPosition(x, y); }               // set the position
void ScoreEntry::Update(const float dt) { lifetime -= dt; } // decrease the lifetime each update

SFMLWorldView::SFMLWorldView(const sf::Texture& texture, const std::shared_ptr<sprites::SpriteAtlas> &atlas,
                             sf::RenderWindow& window, const std::shared_ptr<Camera> &camera)
    : SFMLView(texture, atlas, std::weak_ptr<entities::Entity>(), window, camera), score(0),
      lives(3) {  // create an SFMLView object
    SFMLWorldView::FindSprite(); // find the correct sprite
    // set texture, scale, origin
    sprite.setTexture(texture);
    sprite.setScale(1.f, 1.f);
    sprite.setOrigin(0.f, 0.f);

    // create the 3 pacman life sprites
    life1 = sprite;
    life2 = sprite;
    life3 = sprite;

    // load the correct score font
#ifdef _WIN32
    font.loadFromFile("C:/Windows/Fonts/lucon.ttf"); // Lucida Console
#else
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf");
#endif

    // modify the font
    scoreText.setFont(font);
    scoreText.setLetterSpacing(1.1f);
    scoreText.setFillColor(sf::Color::Yellow);
}

void SFMLWorldView::Update(float dt) {
    // update the score
    scoreText.setString("Score:" + std::to_string(score));
    // update each entry
    std::for_each(scoreEntries.begin(), scoreEntries.end(), [this, dt](ScoreEntry& entry) {
        entry.Update(dt);
        // remove if its lifetime is over
        if (entry.lifetime <= 0.f) {
            toRemove.push_back(entry);
        }
    });
    // remove all entries that needed to be removed
    for (const auto& entry : toRemove) {
        scoreEntries.erase(std::remove_if(scoreEntries.begin(), scoreEntries.end(),
                                          [&entry](const ScoreEntry& e) { return e == entry; }),
                           scoreEntries.end());
    }
    toRemove.clear(); // clear the remove vector
}

void SFMLWorldView::FindSprite() {
    sprite.setTextureRect(atlas->get(sprites::Sprite_ID::PACMAN_RIGHT_2));
} // set the correct sprite for the lives

void SFMLWorldView::Draw() {
    // set the score text position, scaling using the camera class
    const auto screensize = camera->getSpritePixelSize();
    auto screenpos = camera->worldToPixel(0.4, 1.2);
    scoreText.setScale(screensize.x / 32.f, screensize.y / 32.f);
    scoreText.setPosition(screenpos.x, screenpos.y);
    window.draw(scoreText); // draw it on the screen

    // set the correct life1,2,3 positions and scaling using the camera class
    screenpos = camera->worldToPixel(-1, 1);
    life1.setPosition(screenpos.x, screenpos.y);
    life1.setScale(screensize.x / 16.f, screensize.y / 16.f);
    screenpos = camera->worldToPixel(-0.9, 1);
    life2.setPosition(screenpos.x, screenpos.y);
    life2.setScale(screensize.x / 16.f, screensize.y / 16.f);
    screenpos = camera->worldToPixel(-0.8, 1);
    life3.setPosition(screenpos.x, screenpos.y);
    life3.setScale(screensize.x / 16.f, screensize.y / 16.f);

    // and draw them based on how many lives we have left
    if (lives > 0)
        window.draw(life1);
    if (lives > 1)
        window.draw(life2);
    if (lives > 2)
        window.draw(life3);

    // draw each score entry based on its position found by the camera class
    for (auto& entry : scoreEntries) {
        auto screenpos = camera->worldToPixel(entry.position.x, entry.position.y);
        entry.setScale(screensize.x / 16.f, screensize.y / 16.f);
        entry.setPosition(screenpos.x, screenpos.y);
        entry.Draw(window);
    }
}
// simple setters
void SFMLWorldView::setLives(int lives) { this->lives = lives; }
void SFMLWorldView::setScore(int score) { this->score = score; }
void SFMLWorldView::addScoreEntry(const sprites::Sprite_ID ID, const float lifetime, const Position position) {
    // create a score entry
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
void SFMLWorldView::ItemEaten(const sprites::Sprite_ID ID, const Position position) {
    // on an eaten item call the correct addScoreEntry based on the eaten SpriteID
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