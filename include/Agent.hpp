#pragma once

#include "raylib.h"

#include "GridEnvironment.hpp"
#include "Pathfinding.hpp"

class Agent {
public:
    Agent(float x = 0, float y = 0);
    void Input();
    void Update();
    void Render();

    void FindPathToGoal(Pathfinding& pathfinding, const GridEnvironment& environment, Vector2 goal);

    const Vector2& GetPosition() const {
        return position;
    }

private:
    Vector2 position;
    Color color;
    float speed; // Per Second

    std::vector<Waypoint2D> pathRequested;
    Vector2 nextPosition;
};
