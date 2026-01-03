//
// Created by stan1 on 10/11/2025.
//

#include "Score.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

Score::Score(std::string player) : score(0), player(std::move(player)) {} // initiate the variables

void Score::orbEaten() {
    // deduce points for how long ago the last orb was eaten
    if (last_orb_eaten > 5.f) { // cap at a deduction of 5 points
        score += 5;
        last_orb_eaten = 0.f;
        return;
    }
    score += 10 - static_cast<int>(last_orb_eaten); // add the scoring
    last_orb_eaten = 0.f; // reset on eating an orb
}
void Score::PowerOrbEaten() {
    score += 100; // add the scoring
    last_orb_eaten = 0.f; // reset on eating an orb
}
void Score::FruitEaten(sprites::Sprite_ID ID) {
    // add the correct amount of scoring based of which fruit (SpriteID) we ate
    switch (ID) {
    case sprites::Sprite_ID::FRUIT_CHERRY:
        score += 100;
        break;
    case sprites::Sprite_ID::FRUIT_STRAWBERRY:
        score += 300;
        break;
    case sprites::Sprite_ID::FRUIT_ORANGE:
        score += 500;
        break;
    case sprites::Sprite_ID::FRUIT_APPLE:
        score += 700;
        break;
    case sprites::Sprite_ID::FRUIT_MELON:
        score += 1000;
        break;
    case sprites::Sprite_ID::FRUIT_GALAXIAN:
        score += 2000;
        break;
    case sprites::Sprite_ID::FRUIT_BELL:
        score += 3000;
        break;
    case sprites::Sprite_ID::FRUIT_KEY:
        score += 5000;
        break;
    default:
        break;
    }
    last_orb_eaten = 0.f;
}

// add the scoring for eating ghosts, make sure to add the multiplier for combos
void Score::ghostEaten(int combo) { score += 200 * std::pow(2, combo); }

void Score::levelWon() { score += 1000; }; // add scoring for winning a level

void Score::reset() { score = 0; } // reset the score to 0

int Score::getPoints() const { return score; } // simple getter

void Score::Update(float dt) { // update all the timers
    last_orb_eaten += dt;
    if (last_orb_eaten > 5.f) { // if it has been to long since we ate an orb
        decrease_timer += dt;
        if (decrease_timer >= 0.1f) {
            score = std::max(0, score - 1);  // start deducting points
            decrease_timer = 0.f;
        }
    } else if (last_orb_eaten > 1.f) {
        decrease_timer += dt;
        if (decrease_timer >= 0.33f) { // deduct at a slower rate if it has not been that long
            score = std::max(0, score - 1);
            decrease_timer = 0.f;
        }
    }
}

void Score::wright() {
    // write the scores to the scoreboard file
    std::vector<std::pair<std::string, int>> scores;
    std::ifstream inFile("../scoreboard.txt");

    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open scoreboard.txt for reading.\n"; // check if we can open the file
    } else {
        std::string line;
        while (std::getline(inFile, line)) {
            // then go line by line reading in the scores
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

    scores.emplace_back(player, score); // push back the new score

    // sort the scores
    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) { return a.second > b.second; });

    // only show the top 5
    if (scores.size() > 5)
        scores.resize(5);

    // write back into the file
    std::ofstream outFile("../scoreboard.txt", std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open scoreboard.txt for writing.\n"; // check if we can open the file

        return;
    }

    // write all the scores to the file
    for (const auto& entry : scores) {
        const auto& name = entry.first;
        const auto& sc = entry.second;
        outFile << name << ": " << sc << "\n";
    }

    outFile.close(); // close the file at the end
}

Score::~Score() { wright(); } // write to the scoreboard an destruction of this class
