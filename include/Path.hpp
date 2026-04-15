#pragma once

#include <vector>

#include "GridEnvironment.hpp"
#include "Waypoint2D.hpp"

class Path {
public:
    const Waypoint2D& GetCurrentWaypoint();

    const Waypoint2D& GetGoal();

    void FinishCurrentWaypoint(GridEnvironment& environment, int cost);

    bool IsPathCompleted() const { // Are we there yet?
        return pathWaypoints.size() <= 0;
    }

    void AddWaypoint(GridEnvironment& environment, Waypoint2D&& waypoint, int cost);

    void Clear();


private:
    std::vector<Waypoint2D> pathWaypoints;

};


