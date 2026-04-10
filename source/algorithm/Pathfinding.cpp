#include <algorithm>

#include "Pathfinding.hpp"

std::vector<Waypoint2D> Pathfinding::AstarSearch(const GridEnvironment& environment, const Waypoint2D& start, const Waypoint2D& end) {
    std::vector<int> frontier;

    std::vector<int> parentLinearCoordinates(environment.GetSize(), -1);
    std::vector<bool> explored(environment.GetSize(), false);

    const int startLinearCoordinate = environment.WaypointToLinear(start);
    const int endLinearCoordinate = environment.WaypointToLinear(end);
    
    frontier.emplace_back(startLinearCoordinate);

    bool pathFound = false;

    while(!frontier.empty()) {
        int currentLinearCoordinate = frontier.back();
        frontier.pop_back();

        if (currentLinearCoordinate == endLinearCoordinate) {
            pathFound = true;
            break;
        }

        explored[currentLinearCoordinate] = true;

        for (int nextLinearCoordinates : environment.GetNextLinear(currentLinearCoordinate)) {
            if (!explored[nextLinearCoordinates]) { 
                frontier.emplace_back(nextLinearCoordinates);
                parentLinearCoordinates[nextLinearCoordinates] = currentLinearCoordinate;
            } else {
                // update fcost
            }
        }
    }

    // Recover the path
    std::vector<Waypoint2D> path;
    
    if (pathFound) {
        int currentLinearCoordinate = endLinearCoordinate;

        while (currentLinearCoordinate != -1) {
            path.emplace_back(environment.LinearToWaypoint(currentLinearCoordinate));
            currentLinearCoordinate = parentLinearCoordinates[currentLinearCoordinate];
        }

        std::reverse(path.begin(), path.end());
    }

    return path;
}