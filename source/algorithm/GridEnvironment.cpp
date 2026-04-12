#include "GridEnvironment.hpp"

GridEnvironment::GridEnvironment(int width, int height) : width(width), height(height) {
    obstacles.resize(width * height, false);
}


int GridEnvironment::GetSize() const {
    return this->width * this->height;
}


int GridEnvironment::GetWidth() const {
    return this->width;
}


int GridEnvironment::GetHeight() const {
    return this->height;
}


int GridEnvironment::WaypointToLinear(const Waypoint2D& waypoint) const {
    return waypoint.y * this->width + waypoint.x;
}


Waypoint2D GridEnvironment::LinearToWaypoint(int linearCoordinate) const {
    return Waypoint2D(linearCoordinate % this->width, linearCoordinate / this->width);
}


const std::vector<int> GridEnvironment::GetNextLinear(int centerLinearCoordinate) const {
    constexpr int numberOfNextNeighbors = 8;

    std::vector<int> nextLinearCoordinates;
    nextLinearCoordinates.reserve(numberOfNextNeighbors);

    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    
    const int currentX = centerLinearCoordinate % this->width;
    const int currentY = centerLinearCoordinate / this->width;

    if (currentY - 1 >= 0 && !obstacles[centerLinearCoordinate - this->width]) up = true;
    if (currentY + 1 < this->height && !obstacles[centerLinearCoordinate + this->width]) down = true;
    if (currentX - 1 >= 0 && !obstacles[centerLinearCoordinate - 1]) left = true;
    if (currentX + 1 < this->width && !obstacles[centerLinearCoordinate + 1]) right = true;
    
    if (up) nextLinearCoordinates.emplace_back(centerLinearCoordinate - this->width);
    if (down) nextLinearCoordinates.emplace_back(centerLinearCoordinate + this->width);
    if (left) nextLinearCoordinates.emplace_back(centerLinearCoordinate - 1);
    if (right) nextLinearCoordinates.emplace_back(centerLinearCoordinate + 1);
    if (up && left    && !obstacles[centerLinearCoordinate - this->width - 1]) nextLinearCoordinates.emplace_back(centerLinearCoordinate - this->width - 1);
    if (up && right   && !obstacles[centerLinearCoordinate - this->width + 1]) nextLinearCoordinates.emplace_back(centerLinearCoordinate - this->width + 1);
    if (down && left  && !obstacles[centerLinearCoordinate + this->width - 1]) nextLinearCoordinates.emplace_back(centerLinearCoordinate + this->width - 1);
    if (down && right && !obstacles[centerLinearCoordinate + this->width + 1]) nextLinearCoordinates.emplace_back(centerLinearCoordinate + this->width + 1);

    return nextLinearCoordinates;
}


void GridEnvironment::SetObstacle(int x, int y) {
    this->obstacles[y * this->width + x] = true;
}


void GridEnvironment::UnsetObstacle(int x, int y) {
    this->obstacles[y * this->width + x] = false;
}


bool GridEnvironment::IsObstacle(int x, int y) const {
    return this->obstacles[y * this->width + x];
}