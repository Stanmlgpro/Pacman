//
// Created by stan on 10/15/25.
//

#include "Ghost.h"
#include "World.h"
#include "entities/Pacman.h"
#include <climits>
#include <iostream>
#include <queue>

namespace entities {
Ghost::Ghost(float x, float y, std::shared_ptr<Pacman> pacman, const std::vector<std::vector<bool>>& wallgrid, int id,
             float chasetime) {
    // set the variables
    position.x = x;
    position.y = y;
    startpos = {x, y};
    this->pacman = pacman;
    this->wallgrid = wallgrid;
    this->id = id;
    direction = {0, 0};
    feared = false;
    // used for moving evenly in all directions
    mapwidth = static_cast<int>(wallgrid[0].size());
    mapheight = static_cast<int>(wallgrid.size());
    this->ChaseTime = chasetime;
    this->ChaseTimer = chasetime;
    Chasing = false;
    // set collision to check in World class for interactions
    setCollisionSize(1.5f);
}

std::shared_ptr<Entity> Ghost::Interact(World& world) { return world.CollidesWithPacman(shared_from_this()); }

std::vector<std::vector<int>> Ghost::IsAtIntersection() const {
    // find the closests Tile to the position
    auto gridPos = World::NormalizedToGrid(position.x, position.y, wallgrid);
    int gridX = static_cast<int>(gridPos[0]);
    int gridY = static_cast<int>(gridPos[1]);

    // calculate the tileSize and the Center
    float tileSizeX = 2.0f / static_cast<float>(mapwidth);
    float tileSizeY = 2.0f / static_cast<float>(mapheight);
    float cellCenterX = -1.0f + tileSizeX * (static_cast<float>(gridX) + 0.5f);
    float cellCenterY = -1.0f + tileSizeY * (static_cast<float>(gridY) + 0.5f);

    // Check our position agains the position we would snap to if we were to chose the closest tile center
    float distX = std::abs(position.x - cellCenterX);
    float distY = std::abs(position.y - cellCenterY);
    float epsilon = 0.003f;

    // ignore if it becomes to big
    if (!(distX < epsilon && distY < epsilon))
        return {};

    // otherwise create the return value and all the possible directions we need to check
    std::vector<std::vector<int>> ret;
    std::vector<std::vector<int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int openPaths = 0;

    for (const auto& d : dirs) {
        // calculate the next direction
        int nx = gridX + d[0];
        int ny = gridY + d[1];

        // check if this results outside the borders
        if (ny < 0 || ny >= static_cast<int>(wallgrid.size()) || nx < 0 || nx >= static_cast<int>(wallgrid[0].size()))
            continue;

        // check if a wall resides on that tile and add the direction if not
        if (!wallgrid[ny][nx]) {
            openPaths++;
            ret.push_back(d);
        }
    }

    // discard unwanted possible intersections
    // check for to many or single line corridors
    if (openPaths >= 3 || openPaths == 1)
        return ret;

    // check for wanted corner curves
    if (openPaths == 2) {
        bool left = (gridX > 0) && !wallgrid[gridY][gridX - 1];
        bool right = (gridX < static_cast<int>(wallgrid[0].size()) - 1) && !wallgrid[gridY][gridX + 1];
        bool up = (gridY > 0) && !wallgrid[gridY - 1][gridX];
        bool down = (gridY < static_cast<int>(wallgrid.size()) - 1) && !wallgrid[gridY + 1][gridX];

        bool hasHorizontal = left || right;
        bool hasVertical = up || down;

        if (!(hasHorizontal && hasVertical))
            return {};
    }

    // return the possible directions if all nessecities are met
    return ret;
}

void Ghost::Update(float dt) {
    // if we are dying check if we have reached or original position
    if (dying) {
        float EPS = 0.01f;
        // use epsilon comparison becouse of floating point arithmatic
        if (std::abs(position.x - startpos.x) < EPS && std::abs(position.y - startpos.y) < EPS) {
            // stop dying it the original position is reached
            setDying(false);
        }
    }
    // if we are feared update our timer
    if (feared) {
        fearcheck += dt;
        // if the timer reaches the disered time turn of fearmode and reset the timer
        if (fearcheck >= feartime) {
            setFeared(false);
            fearcheck = 0.f;
        }
    }
    // if we are not yet chasin decreased the timer
    if (!Chasing) {
        ChaseTimer -= dt;
        // if it hits 0 we can start chasemode
        if (ChaseTimer <= 0.f) {
            Chasing = true;
        }
        // and update the view since doing it later would result in double updates
        view->Update(dt);
        return;
    }
    // decrease the timer that checks for recent turns done
    if (turnTimer > 0.f)
        turnTimer -= dt;

    // only if we havent turned recently we check for new possible directions to turn
    if (turnTimer <= 0.f)
        CalculateNextTurn(MoveDt(dt));
    // at the end we update our position
    Entity::Update(MoveDt(dt));
    // and our view
    view->Update(dt);
}

void Ghost::setFeared(bool feared) {
    // sets the feared boolean
    // but not if we are dying (in eyes visual)
    if (this->dying and feared)
        return;
    // or if we are already feared we reset the fear checker
    if (this->feared and feared) {
        fearcheck = 0.f;
        return;
    }
    // otherwise we can safely set the boolean
    this->feared = feared;
    // and decrease or increase are speed based on if we are entering or leaving fearmode
    if (feared) {
        fearcheck = 0;
        speed /= 2.f;
    } else
        speed *= 2.f;
}
    // simple getters
bool Ghost::getFeared() { return feared; }
Position Ghost::getStartPos() const { return startpos; }
int Ghost::getId() const { return id; }
float Ghost::MoveDt(float dt) const {
    // create a local variable so we keep our original speed in tact
    auto sped = speed;
    // create even movement in every direction
    if (direction[0] == 1 or direction[0] == -1)
        sped /= mapwidth;
    else
        sped /= mapheight;
    // multiply by our speed
    dt *= sped;
    // return the new value
    return dt;
}
    // simple getters
float Ghost::getFearCheck() const { return fearcheck; }
    // simple setters
void Ghost::setSpeed(float speed) {
    this->speed = speed;
    this->original_speed = speed;
}
    // simple getters
float Ghost::getSpeed() const { return speed; }
void Ghost::setFearTime(float feartime) { this->feartime = feartime; }
bool Ghost::getDying() const { return dying; }

void Ghost::setDying(bool dying) {
    // sets the dying flag
    this->dying = dying;
    // removes fear if we are dying and sets a new speed
    if (dying) {
        setFeared(false);
        speed = 15.f;
    // that is reset on leaving the dying state
    } else
        speed = original_speed;
}

void Ghost::reset() {
    // resets position, direction and all timers
    position = startpos;
    feared = false;
    fearcheck = 0.f;
    Chasing = false;
    ChaseTimer = ChaseTime;
    direction = {0, 0};
}

float Ghost::ManhattanDistance(std::vector<int> direction, Position target, float dt) {
    // calculates the manhattandistance using the new position based on the direction and the dt
    float newX = position.x + direction[0] * speed * dt;
    float newY = position.y + direction[1] * speed * dt;
    float dis = std::abs(newX - target.x) + std::abs(newY - target.y); // formula for distance
    return dis; // and returns it
}

int Ghost::BFSGridDistance(int startX, int startY, int targetX, int targetY) const {
    // uses the BFS algorithm the return the desired distance
    int rows = wallgrid.size();
    int cols = wallgrid[0].size();

    // checks for out for out of bouds
    if (startX < 0 || startX >= cols || startY < 0 || startY >= rows)
        return INT_MAX;
    if (targetX < 0 || targetX >= cols || targetY < 0 || targetY >= rows)
        return INT_MAX;
    // checks if the start or end positions contain a wall
    if (wallgrid[startY][startX] || wallgrid[targetY][targetX])
        return INT_MAX;

    // queue of all positions that need to be checked
    std::queue<std::pair<int, int>> q;
    // 2D vector to store the distance from every position
    std::vector<std::vector<int>> dist(rows, std::vector<int>(cols, -1));

    // push that start position and set its distance to 0
    q.push({startX, startY});
    dist[startY][startX] = 0;

    // all possible directions we need to check
    const std::vector<std::pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    // loop untill nothing more needs to be checked or if we found our target
    while (!q.empty()) {
        // extract the top of the queue
        auto entry = q.front();
        const auto x = entry.first;
        const auto y = entry.second;
        q.pop();

        // check if we found our target
        if (x == targetX && y == targetY)
            return dist[y][x];

        // otherwise add all possible cells we can reach from this one to the queue
        for (auto entry : dirs) {
            const auto dx = entry.first;
            const auto dy = entry.second;
            int nx = x + dx;
            int ny = y + dy;

            // and check for out of bounds
            if (nx < 0 || nx >= cols || ny < 0 || ny >= rows)
                continue;

            // or if we are hitting a wall
            if (!wallgrid[ny][nx] && dist[ny][nx] == -1) {
                dist[ny][nx] = dist[y][x] + 1;
                q.push({nx, ny});
            }
        }
    }

    // last return if we could not find a possible path
    return INT_MAX;
}
float Ghost::BreathFirstDistance(std::vector<int> direction, Position target, float dt) {
    // calulate the positions to call the BFS function on
    auto gpos = World::NormalizedToGrid(position.x, position.y, wallgrid);
    int gx = static_cast<int>(gpos[0]);
    int gy = static_cast<int>(gpos[1]);

    int nextX = gx + direction[0];
    int nextY = gy + direction[1];

    auto tpos = World::NormalizedToGrid(target.x, target.y, wallgrid);
    int tx = static_cast<int>(tpos[0]);
    int ty = static_cast<int>(tpos[1]);

    // calulate the distnace
    int d = BFSGridDistance(nextX, nextY, tx, ty);

    return d; // and return it
}
} // namespace entities