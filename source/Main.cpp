#include <memory>

#include "raylib.h"

#include "GridUI.hpp"

#define WINDOW_W 800
#define WINDOW_H 800
#define WINDOW_N "Grid A* Test"

#define CELL_SIZE 20
#define WIDTH_AS_CELLS 40
#define HEIGHT_AS_CELLS 40


std::unique_ptr<GridUI> gridUI;


// Main loop initialization
void Init() {
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