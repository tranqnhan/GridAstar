#include <cstdio>
#include <memory>

#include "raylib.h"

#include "GridHeap.hpp"
#include "GridUI.hpp"

#define WINDOW_W 1000
#define WINDOW_H 800
#define WINDOW_N "Grid A*"

#define CELL_SIZE 20
#define WIDTH_AS_CELLS 50
#define HEIGHT_AS_CELLS 40


std::unique_ptr<GridUI> gridUI;


// Main loop initialization
void Init() {
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(WINDOW_W, WINDOW_H, WINDOW_N);
    SetTargetFPS(60);

    gridUI = std::make_unique<GridUI>(CELL_SIZE, WIDTH_AS_CELLS, HEIGHT_AS_CELLS);
}


// Main loop input
void Input() {
    gridUI->Input();
}


// Main loop update
void Update(float deltaTime) {
    gridUI->Update();
}


// Main loop draw
void Render() {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawFPS(0, 0);

    gridUI->Render();

    EndDrawing();
}


// Main loop
int main(void) {    
    Init();
    

    while (!WindowShouldClose()) {
        Input();
        Update(GetFrameTime());
        Render();
    }

    CloseWindow();
    return 0;
}