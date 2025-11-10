//
// Created by stan1 on 10/11/2025.
//

#ifndef SCORE_H
#define SCORE_H

class Score {
public:
    Score();
    void orbEaten(bool big);
    void ghostEaten();
    int getPoints() const;
    void reset();

    ~Score();
private:
    int score;
};



#endif //SCORE_H
