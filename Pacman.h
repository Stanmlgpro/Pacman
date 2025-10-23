//
// Created by stan on 10/15/25.
//

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "Entity.h"

class Pacman : public Entity, public std::enable_shared_from_this<Pacman> {
public:
    Pacman(int x, int y);

    std::tuple<std::shared_ptr<Entity>, bool, bool> Interact(Pacman& pacman) override; //should never be called
    std::tuple<std::shared_ptr<Entity>, bool, bool>  InteractWith(std::shared_ptr<Wall> wall);
    std::tuple<std::shared_ptr<Entity>, bool, bool> InteractWith(std::shared_ptr<Orb> orb); // returns true, true if we ate a big orb
    std::tuple<std::shared_ptr<Entity>, bool, bool> InteractWith(std::shared_ptr<Ghost> ghost); // returns ghost if needed to be destroyed bool1 : reset, bool2 : game over

    void Up();
    void Down();
    void Left();
    void Right();

    void Update(float dt) override;

    int getLives() const;

    void setDirection(std::vector<int> direction) override;
    ~Pacman() override = default;
private:
    std::vector<int> direction_buffer;
    bool moving = true;
    int lives = 3;
};


#endif //PACMAN_PACMAN_H