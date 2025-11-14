//
// Created by stan1 on 10/11/2025.
//

#ifndef SCORE_H
#define SCORE_H
#include <string>

class Score {
public:
    Score(std::string player);
    void orbEaten(bool big);
    void ghostEaten();
    int getPoints() const;
    void wright();
    void reset();

    ~Score();
private:
    int score;
    std::string player;
};



#endif //SCORE_H
