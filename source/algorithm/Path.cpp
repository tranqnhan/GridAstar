
#include <vector>

#include "GridEnvironment.hpp"
#include "Waypoint2D.hpp"
#include "Path.hpp"


const Waypoint2D& Path::GetCurrentWaypoint() {
    return pathWaypoints.back().waypoint;
}

const Waypoint2D& Path::GetGoal() {
    return pathWaypoints[0].waypoint;
}


void Path::FinishCurrentWaypoint(GridEnvironment& environment) {
    if (pathWaypoints.size() <= 0) return;
    const PathData& pathData = pathWaypoints.back();
    environment.DecreaseCost(pathData.waypoint.x, pathData.waypoint.y, pathData.cost);
    
    pathWaypoints.pop_back();
}


void Path::AddWaypoint(GridEnvironment& environment, Waypoint2D&& waypoint, int cost) {
    environment.IncreaseCost(waypoint.x, waypoint.y, cost);
    pathWaypoints.emplace_back(std::move(waypoint), cost);
}


void Path::Clear(GridEnvironment& environment) {
    for (const PathData& pathData : pathWaypoints) {
        environment.DecreaseCost(pathData.waypoint.x, pathData.waypoint.y, pathData.cost);
    }
    pathWaypoints.clear();
}