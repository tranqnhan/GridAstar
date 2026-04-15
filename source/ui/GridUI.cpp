#include <raylib.h>
#include <sys/types.h>

#include "GridUI.hpp"
#include "GridEnvironment.hpp"
#include "Program.hpp"
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

    state = GridModifyState::GridState;

    stateNames[GridModifyState::AgentState] = "Agent";
    stateNames[GridModifyState::GridState] = "Grid";

    selectedAgent = -1;
}


void GridUI::Input() {
    if (IsKeyPressed(KEY_Q)) {
        const int currentValue = state;
        if (currentValue < GridModifyState::NumberOfStates - 1) { 
            state = (GridModifyState)(currentValue + 1);
        } else {
            state = (GridModifyState)0;
        }
    }

    if (state == GridModifyState::AgentState) {
        this->AgentStateInput();
    } else {
        this->GridStateInput();
    }

}


void GridUI::GridStateInput() {
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
        const int gridX = GetMouseX() / this->cellSize;
        const int gridY = GetMouseY() / this->cellSize;

        if (gridX < this->widthAsCells && gridY < this->heightAsCells && gridX >= 0 && gridY >= 0) {

            if (this->environment.IsObstacle(gridX, gridY)) {
                this->environment.UnsetObstacle(gridX, gridY);
                ((Color *)this->gridImage.data)[gridY * this->widthAsCells + gridX] = WHITE;
                this->imageChanged = true;  
            }
        }
    } 

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        const int gridX = GetMouseX() / this->cellSize;
        const int gridY = GetMouseY() / this->cellSize;

        if (gridX < this->widthAsCells && gridY < this->heightAsCells && gridX >= 0 && gridY >= 0) {
            if (!this->environment.IsObstacle(gridX, gridY)) {
                this->environment.SetObstacle(gridX, gridY);                
                ((Color *)this->gridImage.data)[gridY * this->widthAsCells + gridX] = BLACK;
                this->imageChanged = true;  
            }
        }
    } 

}


void GridUI::AgentStateInput() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        const float mouseX = GetMouseX();
        const float mouseY = GetMouseY();

        selectedAgent = -1;
        for (int i = 0; i < agents.size(); ++i) {
            const Agent& agent = agents[i];
            const Vector2& position = agent.GetPosition();
            const float dx = position.x - mouseX;
            const float dy = position.y - mouseY;
            if (dx * dx + dy * dy <= (CELL_SIZE / 2.0) * (CELL_SIZE / 2.0)) {
                selectedAgent = i;
                break;
            }
        }
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) { 
        if (selectedAgent != -1) {
            const int gridX = GetMouseX() / this->cellSize;
            const int gridY = GetMouseY() / this->cellSize;

            if (gridX < this->widthAsCells && gridY < this->heightAsCells && gridX >= 0 && gridY >= 0 && 
                !environment.IsObstacle(gridX, gridY)) {
                    end = Waypoint2D(gridX, gridY);
                    findPath = true;
            }
        }
    }

    if (IsKeyPressed(KEY_A)) {
        const int gridX = (GetMouseX() / this->cellSize);
        const int gridY = GetMouseY() / this->cellSize;
        if (gridX < this->widthAsCells && gridY < this->heightAsCells && gridX >= 0 && gridY >= 0 && 
            !environment.IsObstacle(gridX, gridY)) {
                agents.emplace_back(gridX * CELL_SIZE + (CELL_SIZE / 2.0), gridY * CELL_SIZE + (CELL_SIZE / 2.0));
        }
    }

    for (Agent& agent : agents) {
        agent.Input();
    }
}

void GridUI::Update() {
    if (this->findPath) {
        if (this->selectedAgent != -1) {
            // Someone is gonna hate this
            const Vector2 endpos = {.x = (float)end.x * CELL_SIZE, .y = (float) end.y * CELL_SIZE};
            this->agents[this->selectedAgent].FindPathToGoal(pathfinding, environment, endpos);
        }
        this->selectedAgent = -1;
        
        Color *gridImageColor = (Color *)this->gridImage.data;
        this->imageChanged = true;
        this->findPath = false;
    }

    for (Agent& agent : agents) {
        agent.Update(environment);
    }


    if (this->imageChanged) {
        UpdateTexture(this->gridTexture, this->gridImage.data);
        this->imageChanged = false;
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

    if (selectedAgent > -1) {
        const Vector2& selectedAgentPos = agents[selectedAgent].GetPosition();
        DrawCircle(selectedAgentPos.x, selectedAgentPos.y, (CELL_SIZE / 2.0) + 5, BLACK);
    }

    for (Agent& agent : agents) {
        agent.Render();
    }

    DrawText(stateNames[state].c_str(), 0, 0, 12, DARKGREEN);
}