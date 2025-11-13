//
// Created by stan on 10/14/25.
//

#include "MenuState.h"

#include <fstream>
#include "StateManager.h"
#include "LevelState.h"
#include <strstream>
#include <sstream>

MenuState::MenuState(std::shared_ptr<StateManager> statemanager) {
    this->statemanager = statemanager;

    #ifdef _WIN32
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    #else
        font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    #endif

    title = sf::Text("PAC-MAN", font, 60);
    title.setFillColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);

    highscores = loadHighscores("../scoreboard.txt");
    hsTitle = sf::Text("Highscores:", font, 40);
    hsTitle.setFillColor(sf::Color::Cyan);

    hint = sf::Text ("Press ENTER to start", font, 25);
    hint.setFillColor(sf::Color(150,150,150));
}

void MenuState::HandleEvent(const sf::Event &e) {
    if (e.type == sf::Event::TextEntered) {
        char c = static_cast<char>(e.text.unicode);
        if (e.text.unicode == 8) {
            if (!player.empty()) player.pop_back();
        }
        else if ((std::isalnum(c) || c == '_' || c == '-') && player.size() < 16) {
            player += c;
        }
    }
    else if (e.type == sf::Event::KeyPressed) {
        if (e.key.code == sf::Keyboard::Enter) {
            std::cout << "Starting new level with player: " << player << std::endl;
            statemanager->PushState(LEVEL, (player != "") ? player : "Unknown");
        }
    }
}

std::vector<ScoreEntry> MenuState::loadHighscores(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<ScoreEntry> scores;

    if (!file.is_open()) return scores;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        int score;
        if (std::getline(iss, name, ':')) {
            iss >> score;
            name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());
            scores.push_back({name, score});
        }
    }

    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
        return b.score < a.score;
    });

    return scores;
}

void MenuState::Update() {

}

void MenuState::Render(sf::RenderWindow& window) {

    title.setPosition(window.getSize().x / 2.f - title.getGlobalBounds().width / 2.f, 50.f);
    window.draw(title);

    sf::Text playerText("Name: " + player + "_", font, 30);
    playerText.setFillColor(sf::Color::White);
    playerText.setPosition(window.getSize().x / 2.f - playerText.getGlobalBounds().width / 2.f, 150.f);
    window.draw(playerText);

    hsTitle.setPosition(window.getSize().x / 2.f - hsTitle.getGlobalBounds().width / 2.f, 220.f);
    window.draw(hsTitle);

    float y = 280.f;
    int rank = 1;
    for (const auto& s : highscores) {
        std::stringstream ss;
        ss << rank << ". " << s.name << " - " << s.score;
        sf::Text entry(ss.str(), font, 28);
        entry.setFillColor(sf::Color::White);
        entry.setPosition(window.getSize().x / 2.f - entry.getGlobalBounds().width / 2.f, y);
        window.draw(entry);
        y += 35.f;
        if (++rank > 10) break; // Show top 10
    }

    hint.setPosition(window.getSize().x / 2.f - hint.getGlobalBounds().width / 2.f, window.getSize().y - 70.f);
    window.draw(hint);
}

MenuState::~MenuState() = default;
