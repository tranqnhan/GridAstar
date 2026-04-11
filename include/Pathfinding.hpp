#pragma once

#include "Waypoint2D.hpp"
#include "GridEnvironment.hpp"

class Pathfinding {
public:
    std::vector<Waypoint2D> AstarSearch(const GridEnvironment& environment, const Waypoint2D& start, const Waypoint2D& end);

private:
    float EstimateDistance(const Waypoint2D& a, const Waypoint2D& b) const;
    float NextLinearDistance(int currentLinearCoordinate, int nextLinearCoordinate, int width) const;
};
