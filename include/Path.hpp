#pragma once

#include <vector>

#include "GridEnvironment.hpp"
#include "Waypoint2D.hpp"

struct PathData {
    Waypoint2D waypoint;
    int cost;

    PathData(Waypoint2D&& waypoint, int cost) {
        this->waypoint = waypoint;
        this->cost = cost;
    }
};

class Path {
public:
    const Waypoint2D& GetCurrentWaypoint();

    const Waypoint2D& GetGoal();

    void FinishCurrentWaypoint(GridEnvironment& environment);

    bool IsPathCompleted() const { // Are we there yet?
        return pathWaypoints.size() <= 0;
    }

    void AddWaypoint(GridEnvironment& environment, Waypoint2D&& waypoint, int cost);

    void Clear(GridEnvironment& environment);


private:
    std::vector<PathData> pathWaypoints;

};


