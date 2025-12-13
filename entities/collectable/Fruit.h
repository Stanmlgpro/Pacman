//
// Created by stan1 on 12/12/2025.
//

#ifndef FRUIT_H
#define FRUIT_H
#include "./entities/Entity.h"

namespace entities {
    class Fruit : public Entity {
    public:
        Fruit(float x, float y);

        void Update(float dt) override;

        ~Fruit() override = default;
    };

    class Cherry : public Fruit, public std::enable_shared_from_this<Cherry> {
    public:
        Cherry(float x, float y);
        std::shared_ptr<Entity> Interact(World& world) override;
    };

    class Strawberry : public Fruit, public std::enable_shared_from_this<Strawberry> {
    public:
        Strawberry(float x, float y);
        std::shared_ptr<Entity> Interact(World& world) override;
    };

    class Orange : public Fruit, public std::enable_shared_from_this<Orange> {
    public:
        Orange(float x, float y);
        std::shared_ptr<Entity> Interact(World& world) override;
    };

    class Apple : public Fruit, public std::enable_shared_from_this<Apple> {
    public:
        Apple(float x, float y);
        std::shared_ptr<Entity> Interact(World& world) override;
    };

    class Melon : public Fruit, public std::enable_shared_from_this<Melon> {
    public:
        Melon(float x, float y);
        std::shared_ptr<Entity> Interact(World& world) override;
    };

    class Galaxian : public Fruit, public std::enable_shared_from_this<Galaxian> {
    public:
        Galaxian(float x, float y);
        std::shared_ptr<Entity> Interact(World& world) override;
    };

    class Bell : public Fruit, public std::enable_shared_from_this<Bell> {
    public:
        Bell(float x, float y);
        std::shared_ptr<Entity> Interact(World& world) override;
    };

    class Key : public Fruit, public std::enable_shared_from_this<Key> {
    public:
        Key(float x, float y);
        std::shared_ptr<Entity> Interact(World& world) override;
    };
}



#endif //FRUIT_H
