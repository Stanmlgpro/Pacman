//
// Created by stan1 on 14/10/2025.
//

#include "World.h"
#include "Score.h"
#include "entities/Pacman.h"
#include "entities/Wall.h"
#include "entities/collectable/Orb.h"
#include "entities/collectable/PowerOrb.h"
#include "entities/ghost/Ghost.h"
#include "factory/EntityFactory.h"
#include "factory/Sprite_IDs.h"
#include "singleton/Stopwatch.h"
#include "views/View.h"
#include <algorithm>
#include <entities/collectable/Fruit.h>
#include <fstream>
#include <iostream>
#include <utility>

World::World(std::string filename, const std::shared_ptr<factory::EntityFactory>& entity_factory,
             std::shared_ptr<sounds::WorldSound> world_sounds, const std::string& player) {
    // initialize variables
    this->filename = std::move(filename);
    this->entity_factory = entity_factory;
    this->score = std::make_unique<Score>(player);
    this->world_sounds = std::move(world_sounds);
    // std::move since we are using a unique pointer
    this->world_view = std::move(entity_factory->createWorldView());

    dt = 0;
    // base difficulty values
    difficulty = 0;
    fear_time = 7;
    fear_timer = 0;
    combo_timer = 0;
    ghost_speed_mul = 0.4;
    combo_time = 3.f;
    // load the map
    loadMap_reset();
}

void World::loadMap_reset() {
    // increase the difficulty
    // decreasing fear time
    fear_time = fear_time * 0.9f;
    // reset values
    fear_timer = 0;
    combo_timer = 0;
    combo = -1;
    // increasing ghost speed
    ghost_speed_mul = ghost_speed_mul * 1.3f;
    // reset sounds, vectors
    entities.clear();
    wallGrid.clear();
    world_sounds->EndFearMode();
    // read the file
    std::ifstream file(filename);
    std::string line;
    // first calculate the width and height of the map
    // used so we can set the correct map size to the camera
    // and have the correct tile size to normalize all the coordinates
    int width = 0, height = 0;

    while (getline(file, line)) {
        width = std::max(width, static_cast<int>(line.size()));
        height++;
    }
    file.close();

    // set the correct map size
    entity_factory->getCamera()->setMapSize(width, height);
    file.open(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }

    // calculate tile size
    float tileSizeX = 2.0f / static_cast<float>(width);
    float tileSizeY = 2.0f / static_cast<float>(height);

    // helper struct to add the ghost at the end of the level creation, since they need to wallgrid
    // which has yet to be fully created while looping trough the characters
    struct GhostSpawn {
        float x, y;
        int id;
    };
    std::vector<GhostSpawn> ghostSpawns;

    // initiate variables
    int y = 0;
    std::string line2;
    int id = 0;

    while (getline(file, line2)) { // read the file line by line
        wallGrid.emplace_back();   // add another row to the wall grid for each line
        for (int x = 0; x < static_cast<int>(line2.size()); x++) {
            char c = line2[x];                            // read the specific character
            float normX = -1.0f + tileSizeX * (x + 0.5f); // calculate the x value
            float normY = -1.0f + tileSizeY * (y + 0.5f); // calculate the y value

            // create an entity using the entity->factory for each matching symbol (apart from ghosts ofc as explained
            // previously)
            if (c == '#') {
                entities.push_back(entity_factory->createWall(normX, normY));
            } else if (c == '.') {
                entities.push_back(entity_factory->createOrb(normX, normY));
            } else if (c == 'o') {
                entities.push_back(entity_factory->createPowerOrb(normX, normY));
            } else if (c == 'F') {
                entities.push_back(entity_factory->createFruit(normX, normY));
            } else if (c == 'P') {
                pacman = entity_factory->createPacman(7.5f, width, height, normX, normY);
            } else if (c == 'G') {
                ghostSpawns.push_back({normX, normY, id++});
            }

            wallGrid[y].push_back(c == '#'); // set the wall grid accordingly
        }
        y++;
    }
    file.close(); // close the file

    // add a ghost for each ghost spawn struct created
    for (auto& g : ghostSpawns) {
        auto ghost = entity_factory->createGhost(g.x, g.y, pacman, wallGrid, g.id, true);
        ghost->setFearTime(fear_time);
        ghost->setSpeed(ghost->getSpeed() * ghost_speed_mul);
        entities.push_back(ghost);
    }
}

std::vector<int> World::NormalizedToGrid(const float normX, const float normY, const std::vector<std::vector<bool>>& wallGrid) {
    // calculate the width and height of the grid
    const int gridWidth = static_cast<int>(wallGrid[0].size());
    const int gridHeight = static_cast<int>(wallGrid.size());

    // calculate the size of the tiles
    const float tileSizeX = 2.0f / static_cast<float>(gridWidth);
    const float tileSizeY = 2.0f / static_cast<float>(gridHeight);

    // calculate the snapped grid tile
    int gridX = static_cast<int>((normX + 1.0f) / tileSizeX);
    int gridY = static_cast<int>((normY + 1.0f) / tileSizeY);

    return {gridX, gridY}; // return the tile
}

// WHAT FOLLOWS ARE ALL VERRY SIMILAR FUNCTIONS SO ONLY ONCE WILL THE COLLISION CHECKING BE EXPLAINED
std::shared_ptr<entities::Entity> World::CollidesWithPacman(const std::shared_ptr<entities::Wall>& wall) const {
    // get the 2 positions we need
    const Position pacPos = pacman->getPosition();
    const Position wallPos = wall->getPosition();

    // add a tolerance
    constexpr float epsilon = 0.005f;
    // calculate the difference in x and y
    const float dx = std::abs(pacPos.x + static_cast<float>(pacman->getDirection()[0]) * dt - wallPos.x) + epsilon;
    const float dy = std::abs(pacPos.y + static_cast<float>(pacman->getDirection()[1]) * dt - wallPos.y) + epsilon;

    // check for a collision using the collision size
    if (dx < wall->getCollsionSize() / static_cast<float>(wallGrid[0].size()) && dy < wall->getCollsionSize() / static_cast<float>(wallGrid.size()))
        pacman->setMoving(false); // set pacman to stop moving when hitting a wall
    return nullptr;
}

std::shared_ptr<entities::Entity> World::CollidesWithPacman(std::shared_ptr<entities::Orb> orb) const {
    const Position pacPos = pacman->getPosition();
    const Position orbPos = orb->getPosition();

    const float dx = std::abs(pacPos.x + static_cast<float>(pacman->getDirection()[0]) * dt - orbPos.x);
    const float dy = std::abs(pacPos.y + static_cast<float>(pacman->getDirection()[1]) * dt - orbPos.y);

    const float collisionDistX = orb->getCollsionSize() / static_cast<float>(wallGrid[0].size());
    const float collisionDistY = orb->getCollsionSize() / static_cast<float>(wallGrid.size());

    if (dx < collisionDistX && dy < collisionDistY) {
        // on collision play the orb eat sound
        world_sounds->OrbEaten();
        // add the correct scoring
        score->orbEaten();
        // and remove the orb from the game
        return orb;
    }
    return nullptr;
}

std::shared_ptr<entities::Entity> World::CollidesWithPacman(std::shared_ptr<entities::PowerOrb> powerorb) {
    const Position pacPos = pacman->getPosition();
    const Position orbPos = powerorb->getPosition();

    const float dx = std::abs(pacPos.x + static_cast<float>(pacman->getDirection()[0]) * dt - orbPos.x);
    const float dy = std::abs(pacPos.y + static_cast<float>(pacman->getDirection()[1]) * dt - orbPos.y);

    const float collisionDistX = powerorb->getCollsionSize() / static_cast<float>(wallGrid[0].size());
    const float collisionDistY = powerorb->getCollsionSize() / static_cast<float>(wallGrid.size());

    if (dx < collisionDistX && dy < collisionDistY) {
        // on collision play the power orb eat sound
        world_sounds->PowerOrbEaten();
        // add the correct scoring
        score->PowerOrbEaten();
        // add a score entry for the eaten entity
        world_view->ItemEaten(sprites::Sprite_ID::ORB_BIG, pacman->getPosition());
        // reset the fear timer
        fear_timer = 0;
        // activate fearmode
        fearmode = true;
        // remove the power orb from the game
        return powerorb;
    }
    return nullptr;
}

std::shared_ptr<entities::Entity> World::CollidesWithPacman(std::shared_ptr<entities::Fruit> fruit,
                                                            const sprites::Sprite_ID ID) const {
    Position pacPos = pacman->getPosition();
    Position orbPos = fruit->getPosition();

    float dx = std::abs(pacPos.x + static_cast<float>(pacman->getDirection()[0]) * dt - orbPos.x);
    float dy = std::abs(pacPos.y + static_cast<float>(pacman->getDirection()[1]) * dt - orbPos.y);

    float collisionDistX = fruit->getCollsionSize() / static_cast<float>(wallGrid[0].size());
    float collisionDistY = fruit->getCollsionSize() / static_cast<float>(wallGrid.size());

    if (dx < collisionDistX && dy < collisionDistY) {
        // on collision play the fruit eaten sound
        world_sounds->FruitEaten();
        // add the correct scoring based on its ID
        score->FruitEaten(ID);
        // add a score entry for the eaten fruit
        world_view->ItemEaten(ID, pacman->getPosition());
        // remove the fruit from the game
        return fruit;
    }
    return nullptr;
}

std::shared_ptr<entities::Entity> World::CollidesWithPacman(const std::shared_ptr<entities::Ghost>& ghost) {
    if (ghost->getDying())
        return nullptr;
    const Position pacPos = pacman->getPosition();
    const Position ghostPos = ghost->getPosition();

    constexpr float epsilon = 0.005f;
    const float dx = std::abs(pacPos.x + static_cast<float>(pacman->getDirection()[0]) * dt - ghostPos.x) + epsilon;
    const float dy = std::abs(pacPos.y + static_cast<float>(pacman->getDirection()[1]) * dt - ghostPos.y) + epsilon;

    if (dx < ghost->getCollsionSize() / static_cast<float>(wallGrid[0].size()) && dy < ghost->getCollsionSize() / static_cast<float>(wallGrid.size())) {
        // on collision check whether are not the ghost was feared
        if (ghost->getFeared()) {
            // if the ghost was feared set it to be dying
            ghost->setDying(true);
            combo++; // add to the combo
            if (combo > 3) // cap the combo at 4
                combo = 4;
            // add the correct scoring based on the combo
            score->ghostEaten(combo);
            // play the ghost eaten sound
            world_sounds->GhostEaten();
            // add a score entry based on the combo
            switch (combo) {
            case 0:
                world_view->ItemEaten(sprites::Sprite_ID::GHOST_EYES_RIGHT, ghost->getPosition());
                break;
            case 1:
                world_view->ItemEaten(sprites::Sprite_ID::GHOST_EYES_LEFT, ghost->getPosition());
                break;
            case 2:
                world_view->ItemEaten(sprites::Sprite_ID::GHOST_EYES_UP, ghost->getPosition());
                break;
            case 3:
                world_view->ItemEaten(sprites::Sprite_ID::GHOST_EYES_DOWN, ghost->getPosition());
                break;
            default:
                break;
            }
            return nullptr;
        }
        // if the ghost was not feared check if pacman can be damaged
        if (pacman->isDamagable())
            // if he is, play the dying sound
            world_sounds->PacmanDying();
        // take 1 life from pacman
        pacman->setLives(pacman->getLives() - 1);
        // set him te be dying
        pacman->setDying(true);
        if (pacman->getLives() <= 0) {
            // return him if he has no more lives left
            return pacman;
        }
        // and reset all the entities so a new try van begin right after
        for (auto e : entities) {
            e->reset();
        }
    }
    return nullptr;
}

void World::TryBuffer() {
    // read out the direction buffer
    const auto buffer = pacman->getDirectionBuffer();
    if (buffer[0] == 0 && buffer[1] == 0) // check if it was never assigned
        return;

    // calculate the grid x and gri y using the NormlizedToGrid function
    const Position pacPos = pacman->getPosition();
    const auto gridPos = NormalizedToGrid(pacPos.x, pacPos.y, wallGrid);
    const int currentGridX = static_cast<int>(gridPos[0]);
    const int currentGridY = static_cast<int>(gridPos[1]);

    // also calculate the grid x and grid y of where he would be if he took the direction
    const int targetGridX = currentGridX + buffer[0];
    const int targetGridY = currentGridY + buffer[1];

    bool canMove = true; // check if he is allowed to move
    if (targetGridX < 0 or targetGridX >= static_cast<int>(wallGrid[0].size()) or targetGridY < 0 or
        targetGridY >= static_cast<int>(wallGrid.size())) // check for out of bounds movement
        canMove = false;
    else if (wallGrid[targetGridY][targetGridX]) // check if at the new location a wall would reside
        canMove = false;

    if (!canMove) // if is not a valid move, return
        return;

    // otherwise calculate the current position
    const float tileSizeX = 2.0f / static_cast<float>(wallGrid[0].size());
    const float tileSizeY = 2.0f / static_cast<float>(wallGrid.size());

    const float cellCenterX = -1.0f + tileSizeX * (static_cast<float>(currentGridX) + 0.5f);
    const float cellCenterY = -1.0f + tileSizeY * (static_cast<float>(currentGridY) + 0.5f);

    // and calculate the difference between it and the nearest tile center
    const float distX = std::abs(pacPos.x - cellCenterX);
    const float distY = std::abs(pacPos.y - cellCenterY);

    // if it is close enough
    constexpr float epsilon = 0.005f;
    if (distX < epsilon && distY < epsilon)
        pacman->setDirection(
            buffer); // we can take the direction buffer and swap it out for the current actual direction
}

bool World::Update() {
    // check if the game is lost and pacman is not dying anymore
    if (gamelost && !pacman->getDying())
        return true; // return if so
    // calculate the new dt
    singleton::Stopwatch& stopwatch = singleton::Stopwatch::getInstance();
    stopwatch.tick();
    dt = stopwatch.getDeltaTime();
    if (paused) Resume(); // resume sounds if we were paused last update
    if (dt > 0.06f) // and cap at 0.06f to prevent huge jumps on lag spikes from resizing etc...
        dt = 0.06f;
    if (pacman->isDead()) // reset pacman if he is dead
        pacman->reset();
    // add to the combo timer
    if (combo != -1) {
        combo_timer += dt;
        if (combo_timer > combo_time) {
            combo = -1; // and reset the combo if it has been to long
            combo_timer = 0;
        }
    }
    bool new_level =
        true;    // set this bool to true to later call the checkWin function with the see if the level is over
    TryBuffer(); // try the direction buffer currently in pacman
    std::vector<std::shared_ptr<entities::Entity>>
        removeables; // vector to add all items that should be removed into
                     // to prevent deleting from a vector we are looping through
    // loop through all the entities
    for (const auto& e : entities) {
        e->checkWin(new_level);       // check if any orbs, power orbs are still in the level to set the boolean to false
        if (fearmode) {               // if fearmode should be activated
            e->setFeared(fearmode);   // set the entities to fearmode (only has effect on ghosts)
            world_sounds->FearMode(); // and play the fearmode sound
        }
        // add any items that should be removed to the removables vector
        removeables.push_back(e->Interact(*this));
        if (!pacman->getDying()) {
            e->Update(dt); // and if pacman is not dying we can update all the entities
        }
    }
    // update pacman right after all the collision checks
    pacman->Update(dt);
    if (new_level) { // if no orbs, power orbs were left we can start a new level
        // carry over the lives
        const int lives = pacman->getLives();
        // increase the difficulty
        difficulty++;
        // load the map again and increase the ghost speed and decrease the fear time
        loadMap_reset();
        // set pacman to the lives he had before this level
        pacman->setLives(lives);
        // play the new level sound
        world_sounds->Start();
        // add scoring for winning a level
        score->levelWon();
    }
    // loop through all the entities that should be removed
    for (auto& r : removeables) {
        if (r) {
            if (r == pacman)     // if pacman is in them
                gamelost = true; // we lost the level
            // otherwise we can safely remove the entity from the entities vector
            entities.erase(std::remove(entities.begin(), entities.end(), r), entities.end());
        }
    }
    // loop through all the entities that should be added
    for (auto& e : to_add) {
        // and add them to the entities vector
        entities.push_back(e);
    }
    to_add.clear(); // clear the to add vector to eliminate duplicate adding
    // if we are in fearmode we can update our timer
    if (fearmode)
        fear_timer += dt;
    // if we are not and the timer is not 0, we can also increase the timer
    else if (fear_timer != 0) {
        fear_timer += dt;
        // then check if the timer exceeds the fear time
        if (fear_timer > fear_time) {
            // if so reset it
            fear_timer = 0;
            // and play the end fear mode sound
            world_sounds->EndFearMode();
        }
    }
    fearmode = false;                         // reset fear mode
    world_view->setScore(score->getPoints()); // give world view the scoring
    world_view->setLives(pacman->getLives()); // give world view the amount of lives
    world_view->Update(dt);                   // update the world view
    score->Update(dt);                        // update the scoring
    return false;                             // return a default false to indicate the game is not over
}

// simple getter
std::vector<std::shared_ptr<entities::Entity>> World::getEntities() { return entities; }

void World::Render() const {
    // on render we first draw all the entities
    for (const auto& entity : entities) {
        entity->Draw();
    }
    // then draw pacman
    pacman->Draw();
    // and draw the world view as last
    world_view->Draw();
}

void World::movePacman(const MOVE movement) const { // propagate the move command through pacman
    if (movement == UP) {
        pacman->Up();
    }
    if (movement == DOWN) {
        pacman->Down();
    }
    if (movement == LEFT) {
        pacman->Left();
    }
    if (movement == RIGHT) {
        pacman->Right();
    }
}

// unused function, here for polymorphic completeness
std::shared_ptr<entities::Entity> World::CollidesWithPacman(std::shared_ptr<entities::Pacman> pacman) {
    return nullptr;
}

// simple getters
int World::getLives() const { return pacman->getLives(); }
int World::getScore() const { return score->getPoints(); }

void World::Pause() {
    world_sounds->PauseGame();
    paused = true;
}
void World::Resume() {
    world_sounds->ResumeGame();
    paused = false;
}
World::~World() { world_sounds->EndGame(); } // play the endgame sound on destruction of the world