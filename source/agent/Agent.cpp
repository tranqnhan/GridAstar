#include <cmath>

#include "GridEnvironment.hpp"
#include "Program.hpp"

#include "Agent.hpp"
#include "XorshiftRandom.hpp"
#include "Waypoint2D.hpp"
#include "raylib.h"



Agent::Agent(float x, float y, int id) {
    position = Vector2 {x, y};
    nextPosition = position;

    speed = 100;
    color.r = XorshiftRandom::RandomInteger(100, 200);
    color.g = XorshiftRandom::RandomInteger(100, 200);
    color.b = XorshiftRandom::RandomInteger(100, 200);
    color.a = 255;

    this->id = id;
    this->currentWaypointCompleted = false;
    this->followPath = false;
}

void Agent::FindPathToGoal(Pathfinding& pathfinding, GridEnvironment& environment, Vector2 goal) {
    const Waypoint2D start(position.x / CELL_SIZE, position.y / CELL_SIZE);
    const Waypoint2D end(goal.x / CELL_SIZE, goal.y / CELL_SIZE);

    pathfinding.AstarSearch(environment, path, start, end, AGENT_PATH_COST);
    this->currentWaypointCompleted = true;
}


void Agent::Input() {
    if (IsKeyPressed(KEY_SPACE)) {
        this->followPath = true;
    }
}


void Agent::Update(GridEnvironment& environment) {
    FollowPath(environment);
}


void Agent::FollowPath(GridEnvironment& environment) {
    if (!this->followPath) return;

    if (this->currentWaypointCompleted) {
        if(!path.IsPathCompleted()) {
            const Waypoint2D nextWaypoint = path.GetCurrentWaypoint();

            nextPosition = Vector2 {
                .x = (float)nextWaypoint.x * CELL_SIZE + (float)(CELL_SIZE / 2.0), 
                .y = (float)nextWaypoint.y * CELL_SIZE + (float)(CELL_SIZE / 2.0)};
        } else {
            position.x = nextPosition.x;
            position.y = nextPosition.y;
            this->followPath = false;
        }
        this->currentWaypointCompleted = false;
    } else {
        if (!path.IsPathCompleted()) {
            const float dx = nextPosition.x - position.x;
            const float dy = nextPosition.y - position.y;
            const float deltaSecond = GetFrameTime();
            const float deltaSpeed = speed * deltaSecond;
            const float dds = std::sqrt(dx * dx + dy * dy);

            if (dds > deltaSpeed) {
                position.x += (dx / dds) * deltaSpeed;
                position.y += (dy / dds) * deltaSpeed;
            } else { // Lost frame speed
                this->currentWaypointCompleted = true;
                
                path.FinishCurrentWaypoint(environment);
                //position.x = nextPosition.x;
                //position.y = nextPosition.y;
            }
        } else {
            this->followPath = false;
        }
    }
}

void Agent::Render() {
    DrawCircle(this->position.x, this->position.y, CELL_SIZE / 2.0, this->color);
    
    if (!path.IsPathCompleted()) {
        const Waypoint2D& goalWaypoint = path.GetGoal();
        const float goalX = goalWaypoint.x * CELL_SIZE;
        const float goalY = goalWaypoint.y * CELL_SIZE;
        const float radius = CELL_SIZE / 2.0;
        DrawRing(Vector2{.x = goalX + radius, .y = goalY + radius}, radius - 5.0f, radius, 0, 360, 32, this->color); 
    }
}