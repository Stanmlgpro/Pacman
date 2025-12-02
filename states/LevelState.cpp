//
// Created by stan on 10/14/25.
//

#include "LevelState.h"
#include "PausedState.h"
#include "StateManager.h"
#include "World.h"

LevelState::LevelState(std::shared_ptr<StateManager> statemanager, std::shared_ptr<factory::EntityFactory> entity_factory, std::shared_ptr<WorldSound> world_sounds, std::string player) : player(player) {
    this->statemanager = statemanager;
    this->entity_factory = entity_factory;
    this->world_sounds = world_sounds;

    this->world = std::make_unique<World>("../map.txt", entity_factory, world_sounds, player);
    world_sounds->Start();
    std::cout << "new level and world created" << std::endl;

    #ifdef _WIN32
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    #else
        font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    #endif

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    livesText.setFont(font);
    livesText.setCharacterSize(20);
    livesText.setFillColor(sf::Color::Yellow);
}

void LevelState::HandleEvent(const sf::Event &e) {
    if (e.type == sf::Event::KeyPressed) {
        if (e.key.code == sf::Keyboard::Escape) {
            statemanager->PushState(PAUSED, "");
        } else if (e.key.code == sf::Keyboard::Up) {
            world->movePacman(UP);
        } else if (e.key.code == sf::Keyboard::Down) {
            world->movePacman(DOWN);
        } else if (e.key.code == sf::Keyboard::Left) {
            world->movePacman(LEFT);
        } else if (e.key.code == sf::Keyboard::Right) {
            world->movePacman(RIGHT);
        }
    }
}

void LevelState::Update() {
    scoreText.setString("Score: " + std::to_string(world->getScore()));
    livesText.setString("Lives: " + std::to_string(world->getLives()));
    if (world->Update()) {
        statemanager->PopState();
    }
}

void LevelState::Render(sf::RenderWindow& window) {
    world->Render();

    sf::FloatRect worldBounds = window.getView().getViewport();
    sf::Vector2u windowSize = window.getSize();
    livesText.setPosition(windowSize.x - 120, windowSize.y - 40);

    window.draw(scoreText);
    window.draw(livesText);
}

LevelState::~LevelState() = default;