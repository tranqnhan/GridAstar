#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "GridHeap.hpp"
#include "Waypoint2D.hpp"
#include "Pathfinding.hpp"

float Pathfinding::EstimateDistance(const Waypoint2D& a, const Waypoint2D& b) const {
    const int dx = std::abs(a.x - b.x);
    const int dy = std::abs(a.y - b.y);

    if (dx < dy) {
        return 1.4142f * dx + dy;
    } else {
        return 1.4142f * dy + dx;
    }
}


float Pathfinding::NextLinearDistance(int currentLinearCoordinate, int nextLinearCoordinate, int width) const {
    const int diff = std::abs(currentLinearCoordinate - nextLinearCoordinate);
    float result;

    if (diff == 1 || diff == width) {
        result = 1.0f;
    } else {
        result = 1.4142f;
    }
    
    return result;
}


std::vector<Waypoint2D> Pathfinding::AstarSearch(const GridEnvironment& environment, const Waypoint2D& start, const Waypoint2D& end) {
    GridHeap frontier(environment.GetSize());

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
            if (!explored[nextLinearCoordinate]) {
                const Waypoint2D& nextWaypoint = environment.LinearToWaypoint(nextLinearCoordinate);
                const float currentCost = cost[currentLinearCoordinate] + this->NextLinearDistance(currentLinearCoordinate, nextLinearCoordinate, environment.GetWidth());
                const float estimateCost = this->EstimateDistance(nextWaypoint, end);
                const float totalCost = currentCost + estimateCost;

                if (frontier.Push(nextLinearCoordinate, totalCost)) {
                    parentLinearCoordinates[nextLinearCoordinate] = currentLinearCoordinate;
                    cost[nextLinearCoordinate] = currentCost;
                }
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

        std::reverse(path.begin(), path.end());
    }

    return path;
}