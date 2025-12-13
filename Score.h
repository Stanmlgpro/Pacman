//
// Created by stan1 on 10/11/2025.
//

#ifndef SCORE_H
#define SCORE_H
#include <string>
#include "factory/Sprite_IDs.h"

class Score {
public:
    explicit Score(std::string player);
    void orbEaten();
    void PowerOrbEaten();
    void FruitEaten(sprites::Sprite_ID ID);
    void ghostEaten(int combo);
    int getPoints() const;
    void wright();
    void reset();

    void Update(float dt);

    ~Score();
private:
    int score;
    std::string player;
    float last_orb_eaten = 0.f;
    float decrease_timer = 0.f;
};



#endif //SCORE_H
