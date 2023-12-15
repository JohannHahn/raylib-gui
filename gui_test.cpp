#include <iostream>
#include "raylib/src/raylib.h"

int main() {
    InitWindow(900, 600, "TEST");
    while(!WindowShouldClose()) {
	ClearBackground(BLACK);
	BeginDrawing();
	EndDrawing();
    }
    CloseWindow();
    return 0;
}
