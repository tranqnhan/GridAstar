
#include <vector>

#include "GridEnvironment.hpp"
#include "Waypoint2D.hpp"
#include "Path.hpp"


const Waypoint2D& Path::GetCurrentWaypoint() {
    return pathWaypoints.back();
}

const Waypoint2D& Path::GetGoal() {
    return pathWaypoints[0];
}


void Path::FinishCurrentWaypoint(GridEnvironment& environment, int cost) {
    if (pathWaypoints.size() <= 0) return;
    const Waypoint2D& waypoint = pathWaypoints.back();
    environment.DecreaseCost(waypoint.x, waypoint.y, cost);
    pathWaypoints.pop_back();
}


void Path::AddWaypoint(GridEnvironment& environment, Waypoint2D&& waypoint, int cost) {
    environment.IncreaseCost(waypoint.x, waypoint.y, cost);
    pathWaypoints.emplace_back(waypoint);
}


void Path::Clear() {
    pathWaypoints.clear();
}