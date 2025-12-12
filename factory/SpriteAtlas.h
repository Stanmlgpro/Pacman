//
// Created by stan1 on 11/12/2025.
//

#ifndef SPRITEATLAS_H
#define SPRITEATLAS_H
#include <SFML/Graphics.hpp>
#include "factory/Sprite_IDs.h"

namespace sprites {
    class SpriteAtlas {
    public:
        explicit SpriteAtlas(const sf::Texture& texture);

        void load();
        sf::IntRect get(Sprite_ID id) const;
    private:
        sf::Texture texture;
        std::vector<sf::IntRect> spriteRects;
    };
}


#endif //SPRITEATLAS_H
