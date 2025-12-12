//
// Created by stan on 10/15/25.
//

#include "Pacman.h"
#include <iostream>

#include "ghost/Ghost.h"
#include "World.h"

namespace entities {
    Pacman::Pacman(float speed, int mapwidth, int mapheight, float x, float y) : Entity(mapwidth, mapheight) {
        position = {x ,y};
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
        return world.CollidesWithPacman(shared_from_this());
    } //function that will never be called

    void Pacman::Update(float dt) {
        if (!damagable) {
            invincibility_timer += dt;
            if (invincibility_timer > invincibility_duration) {
                damagable = true;
                invincibility_timer = 0.f;
            }
        }
        if (!dying) {
            if (moving) Entity::Update(MoveDt(dt));
            moving = true;
            dying_time = 0;
        }
        else {
            dying_time += dt;
            if (dying_time > 1.6f) {
                setDead(true);
            }
        }
        view->Update(dt);
    }

    int Pacman::getLives() const {
        return lives;
    }
    float Pacman::getSpeed() const {
        return speed;
    }

    void Pacman::setLives(int lives) {
        if (damagable) this->lives = lives;
        damagable = false;
    }

    void Pacman::setMoving(bool moving) {
        this->moving = moving;
    }
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
    void Pacman::setDirectionBuffer(std::vector<int> buffer) {
        direction_buffer = buffer;
    }
    std::vector<int> Pacman::getDirectionBuffer() const {
        return direction_buffer;
    }
    float Pacman::MoveDt(float dt) const {
        auto sped = speed;
        if (direction[0] == 1 or direction[0] == -1) sped /= mapwidth;
        else sped /= mapheight;
        dt *= sped;
        return dt;
    }
    void Pacman::reset() {
        position = startpos;
        dead = false;
        dying = false;
        direction = {0,0};
        direction_buffer = {0,0};
    }
    bool Pacman::isDead() const {
        return dead;
    }
    void Pacman::setDying(bool dying) {
        this->dying = dying;
    }
    bool Pacman::getDying() const {
        return dying;
    }
    void Pacman::setDead(bool dead) {
        this->dead = dead;
    }
    bool Pacman::getDead() const {
        return dead;
    }
    bool Pacman::isDamagable() const {
        return damagable;
    }

}