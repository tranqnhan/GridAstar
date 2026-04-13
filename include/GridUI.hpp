#pragma once

#include "raylib.h"

#include <string>
#include <vector>

#include "Agent.hpp"

#include "Waypoint2D.hpp"
#include "GridEnvironment.hpp"
#include "Pathfinding.hpp"

enum GridModifyState {
    AgentState,
    GridState,
    NumberOfStates
};

class GridUI {
public:
    GridUI(int cellSize, int widthAsCells, int heightAsCells);
    
    void Input();
    void Update();
    void Render();

private:
    Waypoint2D start;
    Waypoint2D end;
    int findPath;

    int cellSize;
    int widthAsCells;
    int heightAsCells;

    Texture2D gridTexture;
    Image gridImage;
    bool imageChanged;

    GridEnvironment environment;
    Pathfinding pathfinding;

    std::vector<Waypoint2D> path;
    std::vector<Agent> agents;
    int selectedAgent;

    GridModifyState state;
    std::string stateNames[GridModifyState::NumberOfStates];

    void GridStateInput();
    void AgentStateInput();
};