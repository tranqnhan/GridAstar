#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "GridHeap.hpp"
#include "Waypoint2D.hpp"
#include "Pathfinding.hpp"

std::vector<Waypoint2D> Pathfinding::AstarSearch(const GridEnvironment& environment, const Waypoint2D& start, const Waypoint2D& end) {
    if (environment.IsObstacle(end.x, end.y)) {
        return std::vector<Waypoint2D>();
    }

    this->frontier.Set(environment.GetSize());

    std::vector<int> parentLinearCoordinates(environment.GetSize(), -1);
    std::vector<float> cost(environment.GetSize(), -1);
    std::vector<bool> explored(environment.GetSize(), false);

    const int startLinearCoordinate = environment.WaypointToLinear(start);
    const int endLinearCoordinate = environment.WaypointToLinear(end);
    
    frontier.Push(startLinearCoordinate, 0);
    cost[startLinearCoordinate] = 0;

    bool pathFound = false;

    int numNodesExplored = 0;

    while(frontier.Size() > 0) {
        const int currentLinearCoordinate = frontier.Pop();

        if (currentLinearCoordinate == endLinearCoordinate) {
            pathFound = true;
            break;
        }

        explored[currentLinearCoordinate] = true;
        numNodesExplored++;

        for (const int nextLinearCoordinate : environment.GetNextLinear(currentLinearCoordinate)) {
            if (explored[nextLinearCoordinate]) continue;

            const Waypoint2D& nextWaypoint = environment.LinearToWaypoint(nextLinearCoordinate);
            
            const int diff = std::abs(currentLinearCoordinate - nextLinearCoordinate);
            const float dCost = (diff == 1 || diff == environment.GetWidth()) ? 1.0f : 1.4142f;
            const float currentCost = cost[currentLinearCoordinate] + dCost;

            const int dxEnd = std::abs(nextWaypoint.x - end.x);
            const int dyEnd = std::abs(nextWaypoint.y - end.y);
            const float estimateCost = (dxEnd < dyEnd) ? (1.4142f * dxEnd + dyEnd) : (1.4142f * dyEnd + dxEnd);
            
            const float totalCost = currentCost + estimateCost;

            if (frontier.Push(nextLinearCoordinate, totalCost)) {
                parentLinearCoordinates[nextLinearCoordinate] = currentLinearCoordinate;
                cost[nextLinearCoordinate] = currentCost;
            }
        }
    }

    printf("num nodes %i\n", numNodesExplored);
    
    // Recover the path
    std::vector<Waypoint2D> path;
    
    if (pathFound) {
        int currentLinearCoordinate = endLinearCoordinate;

        while (currentLinearCoordinate != -1) {
            path.emplace_back(environment.LinearToWaypoint(currentLinearCoordinate));
            currentLinearCoordinate = parentLinearCoordinates[currentLinearCoordinate];
        }

       // std::reverse(path.begin(), path.end());
    }

    return path;
}