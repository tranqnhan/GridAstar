#include <ctime>
#include <memory>

#include "XorshiftRandom.hpp"
#include "raylib.h"

#include "Program.hpp"

#include "GridUI.hpp"


uint32_t XorshiftRandom::randomState = std::time(0);

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