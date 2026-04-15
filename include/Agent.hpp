#pragma once

#include "raylib.h"

#include "GridEnvironment.hpp"
#include "Pathfinding.hpp"

class Agent {
public:
    Agent(float x = 0, float y = 0, int id = 0);
    void Input();
    void Update(GridEnvironment& environment);
    void Render();

    void FindPathToGoal(Pathfinding& pathfinding, GridEnvironment& environment, Vector2 goal);

    const Vector2& GetPosition() const {
        return position;
    }

private:
    Vector2 position;
    Color color;
    float speed; // Per Second
    int id;

    Path path;
    bool currentWaypointCompleted;
    Vector2 nextPosition;
    bool followPath;


    void FollowPath(GridEnvironment& environment);
};
