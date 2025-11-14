//
// Created by stan1 on 10/11/2025.
//

#include "Score.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

Score::Score(std::string player) : score(0), player(player) {}

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
void Score::wright() {
    std::vector<std::pair<std::string, int>> scores;
    std::ifstream inFile("../scoreboard.txt");

    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open scoreboard.txt for reading.\n";
    } else {
        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string name;
            int value;

            if (std::getline(iss, name, ':') && iss >> value) {
                // Trim spaces if any
                name.erase(0, name.find_first_not_of(" \t"));
                name.erase(name.find_last_not_of(" \t") + 1);
                scores.emplace_back(name, value);
            }
        }
        inFile.close();
    }

    scores.emplace_back(player, score);

    std::sort(scores.begin(), scores.end(),
              [](const auto& a, const auto& b) {
                  return a.second > b.second;
              });

    if (scores.size() > 5) scores.resize(5);

    std::ofstream outFile("../scoreboard.txt", std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open scoreboard.txt for writing.\n";
        return;
    }

    for (const auto& [name, sc] : scores) {
        outFile << name << ": " << sc << "\n";
    }

    outFile.close();
}
Score::~Score() {
    wright();
}