//
// Created by stan on 10/15/25.
//

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "Entity.h"

class Pacman : public Entity, public std::enable_shared_from_this<Pacman> {
public:
    Pacman(float speed, int mapwidth, int mapheight, float x, float y);

    std::shared_ptr<Entity> Interact(World& world) override; //should never be called

    void Up();
    void Down();
    void Left();
    void Right();

    void Update(float dt) override;

    void setLives(int lives);
    void setMoving(bool moving);

    int getLives() const;
    float getSpeed() const;

    void setDirectionBuffer(std::vector<int> buffer);
    std::vector<int> getDirectionBuffer() const;
    float MoveDt(float dt) const;

    void setDying(bool dying);
    bool getDying() const override;
    bool getDead() const;
    void setDead(bool dead);
    bool isDead() const;
    void reset() override;

    ~Pacman() override = default;
private:
    std::vector<int> direction_buffer;
    bool moving = true;
    int lives = 3;
    float speed;
    Position startpos;
    bool dying = false;
    bool dead = false;
    float dying_time = 0.f;
};


#endif //PACMAN_PACMAN_H