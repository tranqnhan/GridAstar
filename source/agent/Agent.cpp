#include <cmath>

#include "Program.hpp"

#include "Agent.hpp"
#include "XorshiftRandom.hpp"
#include "Waypoint2D.hpp"
#include "raylib.h"



Agent::Agent(float x, float y, int id) {
    position = Vector2 {x, y};
    nextPosition = position;

    speed = 100;
    color.r = XorshiftRandom::RandomInteger(100, 255);
    color.g = XorshiftRandom::RandomInteger(100, 255);
    color.b = XorshiftRandom::RandomInteger(100, 255);
    color.a = 255;

    this->id = id;
    this->nextWaypoint = false;
}

void Agent::FindPathToGoal(Pathfinding& pathfinding, const GridEnvironment& environment, Vector2 goal) {
    const Waypoint2D start(position.x / CELL_SIZE, position.y / CELL_SIZE);
    const Waypoint2D end(goal.x / CELL_SIZE, goal.y / CELL_SIZE);

    pathRequested = pathfinding.AstarSearch(environment, start, end);
    this->nextWaypoint = true;
}

void Agent::Input() {
}

void Agent::Update() {
    if (this->nextWaypoint) {
        if(pathRequested.size() > 0) {
            const Waypoint2D nextWaypoint = pathRequested.back();

            nextPosition = Vector2 {
                .x = (float)nextWaypoint.x * CELL_SIZE + (float)(CELL_SIZE / 2.0), 
                .y = (float)nextWaypoint.y * CELL_SIZE + (float)(CELL_SIZE / 2.0)};
        } else {
            position.x = nextPosition.x;
            position.y = nextPosition.y;
        }
        this->nextWaypoint = false;
    } else {
        if (pathRequested.size() > 0) {
            const float dx = nextPosition.x - position.x;
            const float dy = nextPosition.y - position.y;
            const float deltaSecond = GetFrameTime();
            const float deltaSpeed = speed * deltaSecond;
            const float dds = std::sqrt(dx * dx + dy * dy);

            if (dds > deltaSpeed) {
                position.x += (dx / dds) * deltaSpeed;
                position.y += (dy / dds) * deltaSpeed;
            } else { // Lost frame speed
                this->nextWaypoint = true;
                pathRequested.pop_back();
                //position.x = nextPosition.x;
                //position.y = nextPosition.y;
            }
        }
    }
}

void Agent::Render() {
    DrawCircle(this->position.x, this->position.y, CELL_SIZE / 2.0, this->color);
    
    DrawCircle(this->position.x, this->position.y, CELL_SIZE / 2.0, this->color);

    if (pathRequested.size() > 0) {
        const float goalX = pathRequested[0].x * CELL_SIZE;
        const float goalY = pathRequested[0].y * CELL_SIZE;
        const float radius = CELL_SIZE / 2.0;
        DrawRing(Vector2{.x = goalX + radius, .y = goalY + radius}, radius - 5.0f, radius, 0, 360, 32, this->color); 
    }
}