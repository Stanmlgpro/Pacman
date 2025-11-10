//
// Created by stan1 on 10/11/2025.
//

#include "Score.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

Score::Score() : score(0) {}

void Score::orbEaten(bool big) {
    if (big) score += 50;
    else score += 10;
}

void Score::ghostEaten() {
    score += 200;
}

void Score::reset() {
    score = 0;
}

int Score::getPoints() const {
    return score;
}

Score::~Score() {
    std::vector<int> scores;
    int s;

    std::ifstream inFile("../scoreboard.txt");

    while (inFile >> s) scores.push_back(s);

    inFile.close();

    scores.push_back(score);

    std::sort(scores.begin(), scores.end(), std::greater<int>());

    if (scores.size() > 5) scores.resize(5);

    std::ofstream outFile("../scoreboard.txt", std::ios::trunc);

    for (int sc : scores) {
        outFile << sc << "\n";
    }
    outFile.close();
}