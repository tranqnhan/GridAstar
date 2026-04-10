#include <raylib.h>

#include "GridUI.hpp"
#include "GridEnvironment.hpp"
#include "Waypoint2D.hpp"

GridUI::GridUI(int cellSize, int widthAsCells, int heightAsCells) :
    cellSize(cellSize), 
    widthAsCells(widthAsCells), 
    heightAsCells(heightAsCells),
    environment(widthAsCells, heightAsCells)
{
    this->findPath = false;

    this->gridImage = GenImageColor(this->widthAsCells, this->heightAsCells, WHITE);
    this->gridTexture = LoadTextureFromImage(gridImage);
    this->imageChanged = false;
}


void GridUI::Input() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        const int gridX = GetMouseX() / this->cellSize;
        const int gridY = GetMouseY() / this->cellSize;

        if (gridX < this->widthAsCells && gridY < this->heightAsCells && gridX >= 0 && gridY >= 0) {

            if (this->environment.GetObstacle(gridX, gridY)) {
                this->environment.UnsetObstacle(gridX, gridY);
                ((Color *)this->gridImage.data)[gridY * this->widthAsCells + gridX] = WHITE;
            } else {
                this->environment.SetObstacle(gridX, gridY);
                ((Color *)this->gridImage.data)[gridY * this->widthAsCells + gridX] = BLACK;
            }

            this->imageChanged = true;        
        }
    } 

    if (IsKeyPressed(KEY_A)) {
        const int gridX = GetMouseX() / this->cellSize;
        const int gridY = GetMouseY() / this->cellSize;

        if (gridX < this->widthAsCells && gridY < this->heightAsCells && gridX >= 0 && gridY >= 0) {
            this->start = Waypoint2D(gridX, gridY);        
        }
    }

    if (IsKeyPressed(KEY_S)) {
        const int gridX = GetMouseX() / this->cellSize;
        const int gridY = GetMouseY() / this->cellSize;

        if (gridX < this->widthAsCells && gridY < this->heightAsCells && gridX >= 0 && gridY >= 0) {
            this->end = Waypoint2D(gridX, gridY);        
        }
    }

    if (IsKeyPressed(KEY_SPACE)) {
        this->findPath = true;
    }
}


void GridUI::Update() {
    if (this->imageChanged) {
        UpdateTexture(this->gridTexture, this->gridImage.data);
        this->imageChanged = false;
    }

    if (this->findPath) {
        this->path = this->pathfinding.AstarSearch(this->environment, this->start, this->end);
        this->findPath = false;
    }
}


void GridUI::Render() {
    DrawTextureEx(this->gridTexture, Vector2 {0, 0}, 0, this->cellSize, WHITE);

    for (int i = 1; i < this->path.size(); ++i) {
        const Waypoint2D& waypoint1 = this->path[i - 1];
        const Waypoint2D& waypoint2 = this->path[i];
        const float startX = (waypoint1.x + 0.5) * this->cellSize;
        const float startY = (waypoint1.y + 0.5) * this->cellSize;
        const float endX = (waypoint2.x + 0.5) * this->cellSize;
        const float endY = (waypoint2.y + 0.5) * this->cellSize;

        DrawLine(startX, startY, endX, endY, DARKGREEN);
    }
}