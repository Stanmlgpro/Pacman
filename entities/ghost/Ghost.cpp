//
// Created by stan on 10/15/25.
//

#include "Ghost.h"
#include "entities/Pacman.h"
#include "World.h"
#include <iostream>
#include <queue>

Ghost::Ghost(float x, float y, std::shared_ptr<Pacman> pacman, const std::vector<std::vector<bool>>& wallgrid, int id, float chasetime) {
    position.x = x;
    position.y = y;
    startpos = {x, y};
    this->pacman = pacman;
    this->wallgrid = wallgrid;
    this->id = id;
    direction = {0, 0};
    feared = false;
    mapwidth = static_cast<int>(wallgrid[0].size());
    mapheight = static_cast<int>(wallgrid.size());
    this->ChaseTime = chasetime;
    this->ChaseTimer = chasetime;
    Chasing = false;
}

std::shared_ptr<Entity> Ghost::Interact(World& world) {
    return world.CollidesWithPacman(shared_from_this());
}

std::vector<std::vector<int>> Ghost::IsAtIntersection() const {
    auto gridPos = World::NormalizedToGrid(position.x, position.y, wallgrid);
    int gridX = static_cast<int>(gridPos[0]);
    int gridY = static_cast<int>(gridPos[1]);

    float tileSizeX = 2.0f / static_cast<float>(wallgrid[0].size());
    float tileSizeY = 2.0f / static_cast<float>(wallgrid.size());
    float cellCenterX = -1.0f + tileSizeX * (static_cast<float>(gridX) + 0.5f);
    float cellCenterY = -1.0f + tileSizeY * (static_cast<float>(gridY) + 0.5f);

    float distX = std::abs(position.x - cellCenterX);
    float distY = std::abs(position.y - cellCenterY);
    float epsilon = 0.003f;

    if (!(distX < epsilon && distY < epsilon))
        return {};

    std::vector<std::vector<int>> ret;
    std::vector<std::vector<int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int openPaths = 0;

    for (const auto& d : dirs) {
        int nx = gridX + d[0];
        int ny = gridY + d[1];

        if (ny < 0 || ny >= static_cast<int>(wallgrid.size()) ||
            nx < 0 || nx >= static_cast<int>(wallgrid[0].size()))
            continue;

        if (!wallgrid[ny][nx]) {
            openPaths++;
            ret.push_back(d);
        }
    }

    if (openPaths >= 3 || openPaths == 1)
        return ret;

    if (openPaths == 2) {
        bool left = (gridX > 0) && !wallgrid[gridY][gridX - 1];
        bool right = (gridX < static_cast<int>(wallgrid[0].size()) - 1) && !wallgrid[gridY][gridX + 1];
        bool up = (gridY > 0) && !wallgrid[gridY - 1][gridX];
        bool down = (gridY < static_cast<int>(wallgrid.size()) - 1) && !wallgrid[gridY + 1][gridX];

        bool hasHorizontal = left || right;
        bool hasVertical   = up || down;

        if (!(hasHorizontal && hasVertical))
            return {};
    }

    return ret;
}

void Ghost::Update(float dt) {
    if (dying) {
        float EPS = 0.01f;
        if (std::abs(position.x - startpos.x) < EPS && std::abs(position.y - startpos.y) < EPS) {
            setDying(false);
        }
    }
    if (feared) {
        fearcheck += dt;
        if (fearcheck >= feartime) {
            setFeared(false);
            fearcheck = 0.f;
        }
    }
    if (!Chasing) {
        ChaseTimer -= dt;
        if (ChaseTimer <= 0.f) {
            Chasing = true;
        }
        view->Update(dt);
        return;
    }
    if (turnTimer > 0.f)
        turnTimer -= dt;

    if (turnTimer <= 0.f)
        CalculateNextTurn(MoveDt(dt));
    Entity::Update(MoveDt(dt));
    view->Update(dt);
}

void Ghost::setFeared(bool feared) {
    this->feared = feared;
    if (feared) {
        fearcheck = 0;
        speed /= 2.f;
    }
    else speed *= 2.f;
}
bool Ghost::getFeared() {
    return feared;
}
Position Ghost::getStartPos() const {
    return startpos;
}
int Ghost::getId() const {
    return id;
}
float Ghost::MoveDt(float dt) const {
    auto sped = speed;
    if (direction[0] == 1 or direction[0] == -1) sped /= mapwidth;
    else sped /= mapheight;
    dt *= sped;
    return dt;
}
float Ghost::getFearCheck() const {
    return fearcheck;
}
void Ghost::setSpeed(float speed) {
    this->speed = speed;
}
float Ghost::getSpeed() const {
    return speed;
}
void Ghost::setFearTime(float feartime) {
    this->feartime = feartime;
}
bool Ghost::getDying() const {
    return dying;
}

void Ghost::setDying(bool dying) {
    this->dying = dying;
    if (dying) {
        setFeared(false);
        speed *= 4;
    }
    else speed /= 4;
}

void Ghost::reset() {
    position = startpos;
    feared = false;
    fearcheck = 0.f;
    Chasing = false;
    ChaseTimer = ChaseTime;
    direction = {0,0};
}

float Ghost::ManhattanDistance(std::vector<int> direction, Position target, float dt) {
    float newX = position.x + direction[0] * speed * dt;
    float newY = position.y + direction[1] * speed * dt;
    float dis = std::abs(newX - target.x) + std::abs(newY - target.y);
    return dis;
}

int Ghost::BFSGridDistance(int startX, int startY, int targetX, int targetY) const {
    int rows = wallgrid.size();
    int cols = wallgrid[0].size();

    if (startX < 0 || startX >= cols || startY < 0 || startY >= rows) return INT_MAX;
    if (targetX < 0 || targetX >= cols || targetY < 0 || targetY >= rows) return INT_MAX;
    if (wallgrid[startY][startX] || wallgrid[targetY][targetX]) return INT_MAX;

    std::queue<std::pair<int,int>> q;
    std::vector<std::vector<int>> dist(rows, std::vector<int>(cols, -1));

    q.push({startX, startY});
    dist[startY][startX] = 0;

    const std::vector<std::pair<int,int>> dirs = {
        {1,0}, {-1,0}, {0,1}, {0,-1}
    };

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == targetX && y == targetY)
            return dist[y][x];

        for (auto [dx, dy] : dirs) {
            int nx = x + dx;
            int ny = y + dy;

            if (nx < 0 || nx >= cols || ny < 0 || ny >= rows)
                continue;

            if (!wallgrid[ny][nx] && dist[ny][nx] == -1) {
                dist[ny][nx] = dist[y][x] + 1;
                q.push({nx, ny});
            }
        }
    }

    return INT_MAX;
}
float Ghost::BreathFirstDistance(std::vector<int> direction, Position target, float dt)
{
    auto gpos = World::NormalizedToGrid(position.x, position.y, wallgrid);
    int gx = static_cast<int>(gpos[0]);
    int gy = static_cast<int>(gpos[1]);

    int nextX = gx + direction[0];
    int nextY = gy + direction[1];

    auto tpos = World::NormalizedToGrid(target.x, target.y, wallgrid);
    int tx = static_cast<int>(tpos[0]);
    int ty = static_cast<int>(tpos[1]);

    int d = BFSGridDistance(nextX, nextY, tx, ty);

    return d;
}