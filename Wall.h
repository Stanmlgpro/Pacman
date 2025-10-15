//
// Created by stan on 10/15/25.
//

#ifndef PACMAN_WALL_H
#define PACMAN_WALL_H
#include "Entity.h"

class Wall : public Entity {
public:
    Wall(int x, int y);

    void Update(float dt) override;
    void Interact(std::shared_ptr<Entity> other) override;

    ~Wall();
private:
    Position position;
};


#endif //PACMAN_WALL_H