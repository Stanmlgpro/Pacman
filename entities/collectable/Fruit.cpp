//
// Created by stan1 on 12/12/2025.
//

#include "Fruit.h"
#include "World.h"
#include <iostream>

namespace entities {
Fruit::Fruit(float x, float y) {
    // Create A fruit and give at a position and collision
    position.x = x;
    position.y = y;
    setCollisionSize(1.25f);
}

void Fruit::Update(const float dt) { view->Update(dt); }

// Override Interact functions to signal back to the world which entity we are dealing with
Cherry::Cherry(const float x, const float y) : Fruit(x, y) {}
std::shared_ptr<Entity> Cherry::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this(), sprites::Sprite_ID::FRUIT_CHERRY);
}

Strawberry::Strawberry(const float x, const float y) : Fruit(x, y) {}
std::shared_ptr<Entity> Strawberry::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this(), sprites::Sprite_ID::FRUIT_STRAWBERRY);
}

Orange::Orange(const float x, const float y) : Fruit(x, y) {}
std::shared_ptr<Entity> Orange::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this(), sprites::Sprite_ID::FRUIT_ORANGE);
}

Apple::Apple(const float x, const float y) : Fruit(x, y) {}
std::shared_ptr<Entity> Apple::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this(), sprites::Sprite_ID::FRUIT_APPLE);
}

Melon::Melon(const float x, const float y) : Fruit(x, y) {}
std::shared_ptr<Entity> Melon::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this(), sprites::Sprite_ID::FRUIT_MELON);
}

Galaxian::Galaxian(const float x, const float y) : Fruit(x, y) {}
std::shared_ptr<Entity> Galaxian::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this(), sprites::Sprite_ID::FRUIT_GALAXIAN);
}

Bell::Bell(const float x, const float y) : Fruit(x, y) {}
std::shared_ptr<Entity> Bell::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this(), sprites::Sprite_ID::FRUIT_BELL);
}

Key::Key(const float x, const float y) : Fruit(x, y) {}
std::shared_ptr<Entity> Key::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this(), sprites::Sprite_ID::FRUIT_KEY);
}
} // namespace entities