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


void GridHeapTest() {
    GridHeap heap(100);

    heap.Push(2, 2);
    heap.Push(5, 5);
    heap.Push(3, 3);
    heap.Push(4, 4);
    heap.Push(1, 1);

    heap.Push(4, 2);

    heap.Pop();

    heap.Push(0, 0);

    heap.Push(4, -1);

    const int heapSize = heap.Size();
    for (int i = 0; i < heapSize; ++i) {
        std::printf("%i ", heap.Pop());
        std::fflush(stdout);
    }
    std::printf("\n");

    // 4 0 2 3 5
}


void Test() {
    GridHeapTest();
}


// Main loop
int main(void) {
    // Test();
    
    Init();
    

    while (!WindowShouldClose()) {
        Input();
        Update(GetFrameTime());
        Render();
    }

    CloseWindow();
    return 0;
}