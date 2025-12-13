//
// Created by stan1 on 12/12/2025.
//

#ifndef SFMLFRUITVIEW_H
#define SFMLFRUITVIEW_H
#include <views/SFMLView.h>

namespace views {
    class SFMLFruitView : public SFMLView {
    public:
        SFMLFruitView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);

        void Update(float dt) override;

        void Draw() override;
    };

    class SFMLCherryView : public SFMLFruitView {
    public:
        SFMLCherryView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
        void FindSprite() override;
    };

    class SFMLStrawberryView : public SFMLFruitView {
    public:
        SFMLStrawberryView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
        void FindSprite() override;
    };

    class SFMLMelonView : public SFMLFruitView {
    public:
        SFMLMelonView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
        void FindSprite() override;
    };

    class SFMLAppleView : public SFMLFruitView {
    public:
        SFMLAppleView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
        void FindSprite() override;
    };

    class SFMLOrangeView : public SFMLFruitView {
    public:
        SFMLOrangeView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
        void FindSprite() override;
    };

    class SFMLGalaxianView : public SFMLFruitView {
    public:
        SFMLGalaxianView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
        void FindSprite() override;
    };

    class SFMLBellView : public SFMLFruitView {
    public:
        SFMLBellView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
        void FindSprite() override;
    };

    class SFMLKeyView : public SFMLFruitView {
    public:
        SFMLKeyView(const sf::Texture& texture, std::shared_ptr<sprites::SpriteAtlas> atlas, std::weak_ptr<entities::Entity> entity, sf::RenderWindow& window, std::shared_ptr<Camera> camera);
        void FindSprite() override;
    };
}


#endif //SFMLFRUITVIEW_H
