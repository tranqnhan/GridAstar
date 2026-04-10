#pragma once

#include <vector>

#include "Waypoint2D.hpp"

class GridEnvironment {
public:
    GridEnvironment(int width, int height);

    int GetSize() const;
    int GetWidth() const;
    int GetHeight() const;
    int WaypointToLinear(const Waypoint2D& waypoint) const;
    Waypoint2D LinearToWaypoint(int linearCoordinate) const;
    const std::vector<int> GetNextLinear(int centerLinearCoordinate) const;

    void SetObstacle(const Waypoint2D& waypoint);
    void SetObstacle(int x, int y);
    void UnsetObstacle(const Waypoint2D& waypoint);
    void UnsetObstacle(int x, int y);
    bool GetObstacle(int x, int y) const;

private:
    int width;
    int height;

    std::vector<bool> obstacles;

};

