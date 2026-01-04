//
// Created by stan1 on 12/12/2025.
//

#ifndef SFMLWORLDVIEW_H
#define SFMLWORLDVIEW_H
#include "SFMLView.h"
#include <entities/Entity.h>
/**
 * @file SFMLWorldView.h
 * @brief SFMLWorldView Class
 */
namespace views {
/**
 * @struct ScoreEntry
 * @brief Visual scores
 *
 * Visuals for score numbers (100, 200, ...)
 */
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

class SFMLWorldView final : public SFMLView {
    /**
     * @class SFMLWorldView
     * @brief SFMLWorldView class
     *
     * View for the world
     */
public:
    /**
     * @brief Creates a SFMLWorldView object.
     * @param texture texture of which to get the sprites
     * @param atlas atlast from where we get the correct rectangles to get our sprites from
     * @param window window to draw the sprites onto
     * @param camera camera to calculate the correct position to draw the sprites
     */
    SFMLWorldView(const sf::Texture& texture, const std::shared_ptr<sprites::SpriteAtlas>& atlas,
                  sf::RenderWindow& window, const std::shared_ptr<Camera>& camera);
    /// Overrides SFMLView::Update
    void Update(float dt) override;
    /// Overrides SFMLView::FindSprite
    void FindSprite() override;
    /**
     * @brief adds a score entry
     *
     * creates a new score entry with the correct sprite using the atlas and spriteID
     *
     * @param ID to find the correct sprite
     * @param lifetime time the score will be visible
     * @param position position the score needs to be placed
     */
    void addScoreEntry(sprites::Sprite_ID ID, float lifetime, Position position);

    /**
     * @brief Sets lives
     * @param lives
     */
    void setLives(int lives) override;
    /**
     * @brief Sets score
     * @param score
     */
    void setScore(int score) override;
    /**
     * @brief called when a score entry should be created on item eating
     *
     * calls addScoreEntry based on the position of the eaton object
     * and its sprite_ID
     *
     * @param ID to find the correct sprite
     * @param position position the score needs to be placed
     */
    void ItemEaten(sprites::Sprite_ID ID, Position position) override;
    /// Overrides SFMLView::Draw
    void Draw() override;

    ~SFMLWorldView() override = default;

private:
    /** font, text for score */
    sf::Font font;
    sf::Text scoreText;
    /** sprites for pacman lives */
    sf::Sprite life1;
    sf::Sprite life2;
    sf::Sprite life3;
    int score;
    int lives;
    std::vector<ScoreEntry> scoreEntries;
    /** vector to prevent removing score entries while looping over them */
    std::vector<ScoreEntry> toRemove;
};
} // namespace views

#endif // SFMLWORLDVIEW_H
