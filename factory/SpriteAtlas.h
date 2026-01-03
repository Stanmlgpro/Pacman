//
// Created by stan1 on 11/12/2025.
//

#ifndef SPRITEATLAS_H
#define SPRITEATLAS_H
#include "factory/Sprite_IDs.h"
#include <SFML/Graphics.hpp>
/**
 * @file SpriteAtlas.h
 * @brief SpriteAtlas Class
 */
namespace sprites {
    /**
* @class SpriteAtlas
* @brief precuts rectangles from the texture
*
* holds all rectangles for each possible entity model in the spriteID enum
*/
class SpriteAtlas {
public:
    /**
* @brief Creates a SpriteAtlas object.
* @param texture the texture we cut from
*/
    explicit SpriteAtlas(const sf::Texture& texture);
    /**
* @brief predefined the rectangles
*/
    void load();
    /**
  * @brief returns the rectangle based on the requested SpriteID
  *
  * @param id requested ID
  * @return the Rectangle needed for the sprite
  */
    sf::IntRect get(Sprite_ID id) const;

    ~SpriteAtlas() = default;

private:
    sf::Texture texture;
    /** vector of all rectangles, 1 for each entry in the enum (vector in this case) */
    std::vector<sf::IntRect> spriteRects;
};
} // namespace sprites

#endif // SPRITEATLAS_H
