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

    void setDirection(std::vector<int> direction) override;
    ~Pacman() override = default;
private:
    std::vector<int> direction_buffer;
    bool moving = true;
    int lives = 3;
    float speed;
};


#endif //PACMAN_PACMAN_H