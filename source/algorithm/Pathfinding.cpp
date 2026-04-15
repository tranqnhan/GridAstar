#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "GridHeap.hpp"
#include "Waypoint2D.hpp"
#include "Path.hpp"
#include "Pathfinding.hpp"

void Pathfinding::AstarSearch(GridEnvironment& environment, Path& path, const Waypoint2D& start, const Waypoint2D& end, int agentCost) {
    path.Clear();

    if (environment.IsObstacle(end.x, end.y)) {
        return;
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
            
            constexpr float diagonalCost = 1.4142f;
            constexpr float straightCost = 1.0f;

            const int diff = std::abs(currentLinearCoordinate - nextLinearCoordinate);
            const float dCost = (diff == 1 || diff == environment.GetWidth()) ? straightCost : diagonalCost;
            const float currentCost = cost[currentLinearCoordinate] + dCost + environment.GetCost(nextLinearCoordinate);

            const int dxEnd = std::abs(nextWaypoint.x - end.x);
            const int dyEnd = std::abs(nextWaypoint.y - end.y);
            const float estimateCost = (dxEnd < dyEnd) ? (diagonalCost * dxEnd + dyEnd) : (diagonalCost * dyEnd + dxEnd);
            
            const float totalCost = currentCost + estimateCost;

            if (frontier.Push(nextLinearCoordinate, totalCost)) {
                parentLinearCoordinates[nextLinearCoordinate] = currentLinearCoordinate;
                cost[nextLinearCoordinate] = currentCost;
            }
        }
    }

    printf("num nodes %i\n", numNodesExplored);
    
    // Recover the path
    
    if (pathFound) {
        int currentLinearCoordinate = endLinearCoordinate;

        while (currentLinearCoordinate != -1) {
            path.AddWaypoint(environment, std::move(environment.LinearToWaypoint(currentLinearCoordinate)), agentCost);
            currentLinearCoordinate = parentLinearCoordinates[currentLinearCoordinate];
        }
    }
}