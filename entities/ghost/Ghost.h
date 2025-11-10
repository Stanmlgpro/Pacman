//
// Created by stan on 10/15/25.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "entities/Entity.h"

class Ghost : public Entity, public std::enable_shared_from_this<Ghost> {
public:
    Ghost(float x, float y, std::shared_ptr<Pacman> pacman, const std::vector<std::vector<bool>>& wallgrid, int id, float chasetime);

    std::vector<std::vector<int>> IsAtIntersection() const;
    virtual float distanceTurn(std::vector<int> direction, float dt) = 0;
    virtual void CalculateNextTurn(float dt) = 0;

    std::shared_ptr<Entity> Interact(World& world) override;

    void Update(float dt) override;

    void setFeared(bool feared);
    bool getFeared();
    std::vector<float> getStartPos() const;
    int getId() const;
    float MoveDt(float dt) const;

    ~Ghost() override = default;
protected:
    std::shared_ptr<Pacman> pacman;
    std::vector<std::vector<bool>> wallgrid;
    std::vector<float> startpos;
    bool feared = false;
    float feartime = 6.f;
    float fearcheck = 0.f;
    int id;
    float speed;
    float ChaseTime;
    bool Chasing;
};


#endif //PACMAN_GHOST_H