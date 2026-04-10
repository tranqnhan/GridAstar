#pragma once

#include "Waypoint2D.hpp"
#include "GridEnvironment.hpp"

class Pathfinding {
public:
    std::vector<Waypoint2D> AstarSearch(const GridEnvironment& environment, const Waypoint2D& start, const Waypoint2D& end);
};
