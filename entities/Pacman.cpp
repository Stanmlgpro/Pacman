//
// Created by stan on 10/15/25.
//

#include "Pacman.h"
#include <iostream>

#include "World.h"
#include "ghost/Ghost.h"

namespace entities {
Pacman::Pacman(float speed, int mapwidth, int mapheight, float x, float y) : Entity(mapwidth, mapheight) {
    // set all variables
    position = {x, y};
    direction.reserve(2);
    direction.push_back(1);
    direction.push_back(0);
    direction_buffer.reserve(2);
    direction_buffer.push_back(0);
    direction_buffer.push_back(0);
    startpos = {x, y};
    this->speed = speed;
    setCollisionSize(2.0f);
}

std::shared_ptr<Entity> Pacman::Interact(World& world) {
    // implemented for consistency
    return world.CollidesWithPacman(shared_from_this());
} // function that should never be called

void Pacman::Update(float dt) {
    // check if we are damageable, and if not decrouse our timer
    if (!damagable) {
        invincibility_timer += dt;
        // and make us damageable if if reaches the duration
        if (invincibility_timer > invincibility_duration) {
            damagable = true;
            // reset the timer
            invincibility_timer = 0.f;
        }
    }
    // only try moving if we are not dead
    if (!dying) {
        // if we can move Update our position, otherwise set moving to true and reset the timer that checks for dying
        if (moving)
            Entity::Update(MoveDt(dt));
        moving = true;
        dying_time = 0;
    // otherwise update the amount of time we are dying
    } else {
        dying_time += dt;
        // and set us to dead if we reach above the 1.6f cap
        if (dying_time > 1.6f) {
            setDead(true);
        }
        // and make is immune in the process
        damagable = false;
    }
    // update the view at the verry end
    view->Update(dt);
}
// simple getters
int Pacman::getLives() const { return lives; }
float Pacman::getSpeed() const { return speed; }

void Pacman::setLives(int lives) {
    // check if we can be damaged before setting lives
    if (damagable)
        this->lives = lives;
    damagable = false;
}
// simple setter
void Pacman::setMoving(bool moving) { this->moving = moving; }
// set the direction buffer to the correct value on every input
void Pacman::Up() {
    direction_buffer[0] = 0;
    direction_buffer[1] = -1;
}
void Pacman::Down() {
    direction_buffer[0] = 0;
    direction_buffer[1] = 1;
}
void Pacman::Left() {
    direction_buffer[0] = -1;
    direction_buffer[1] = 0;
}
void Pacman::Right() {
    direction_buffer[0] = 1;
    direction_buffer[1] = 0;
}
// more simple getters / setters
void Pacman::setDirectionBuffer(std::vector<int> buffer) { direction_buffer = buffer; }
std::vector<int> Pacman::getDirectionBuffer() const { return direction_buffer; }
float Pacman::MoveDt(float dt) const {
    // create a local variable so we keep our original speed in tact
    auto sped = speed;
    // create even movement in every direction
    if (direction[0] == 1 or direction[0] == -1)
        sped /= mapwidth;
    else
        sped /= mapheight;
    // multiply by our speed
    dt *= sped;
    // return the new value
    return dt;
}
void Pacman::reset() {
    // reset the position, direction and reset dead, dying flags
    position = startpos;
    dead = false;
    dying = false;
    direction = {0, 0};
    direction_buffer = {0, 0};
}
// simple getters/ setters
bool Pacman::isDead() const { return dead; }
void Pacman::setDying(bool dying) { this->dying = dying; }
bool Pacman::getDying() const { return dying; }
void Pacman::setDead(bool dead) {
    // make sure to set the dying state to false when we are dead
    this->dead = dead;
    this->dying = false;
}
bool Pacman::isDamagable() const { return damagable; }

} // namespace entities