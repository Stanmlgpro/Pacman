//
// Created by stan1 on 06/11/2025.
//

#ifndef SFMLVIEW_H
#define SFMLVIEW_H
#include "View.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
namespace views {
    class SFMLView : public View {
    public:
        SFMLView(const sf::Texture& texture, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);

        void Update(float dt) override = 0;

        void Draw() override = 0;

    protected:
        sf::Texture texture;
        sf::RenderWindow& window;
    };
}


#endif //SFMLVIEW_H
