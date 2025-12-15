//
// Created by stan1 on 12/12/2025.
//

#include "Fruit.h"
#include "World.h"
#include <iostream>

namespace entities {
Fruit::Fruit(float x, float y) {
    position.x = x;
    position.y = y;
    setCollisionSize(1.25f);
}

void Fruit::Update(float dt) { view->Update(dt); }

Cherry::Cherry(float x, float y) : Fruit(x, y) {}
std::shared_ptr<Entity> Cherry::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this(), sprites::Sprite_ID::FRUIT_CHERRY);
}

Strawberry::Strawberry(float x, float y) : Fruit(x, y) {}
std::shared_ptr<Entity> Strawberry::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this(), sprites::Sprite_ID::FRUIT_STRAWBERRY);
}

Orange::Orange(float x, float y) : Fruit(x, y) {}
std::shared_ptr<Entity> Orange::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this(), sprites::Sprite_ID::FRUIT_ORANGE);
}

Apple::Apple(float x, float y) : Fruit(x, y) {}
std::shared_ptr<Entity> Apple::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this(), sprites::Sprite_ID::FRUIT_APPLE);
}

Melon::Melon(float x, float y) : Fruit(x, y) {}
std::shared_ptr<Entity> Melon::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this(), sprites::Sprite_ID::FRUIT_MELON);
}

Galaxian::Galaxian(float x, float y) : Fruit(x, y) {}
std::shared_ptr<Entity> Galaxian::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this(), sprites::Sprite_ID::FRUIT_GALAXIAN);
}

Bell::Bell(float x, float y) : Fruit(x, y) {}
std::shared_ptr<Entity> Bell::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this(), sprites::Sprite_ID::FRUIT_BELL);
}

Key::Key(float x, float y) : Fruit(x, y) {}
std::shared_ptr<Entity> Key::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this(), sprites::Sprite_ID::FRUIT_KEY);
}
} // namespace entities