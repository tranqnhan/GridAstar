#pragma once

#include "GridHeap.hpp"
#include "Waypoint2D.hpp"
#include "Path.hpp"
#include "GridEnvironment.hpp"

class Pathfinding {
public:
    void AstarSearch(GridEnvironment& environment, Path& path, const Waypoint2D& start, const Waypoint2D& end, int agentCost);

private:
    GridHeap frontier;
};
