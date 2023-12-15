#include <iostream>
#include "layout.h"

int main() {
    InitWindow(900, 600, "TEST");

    Layout layout({0, 1, 2, 3}, 2, 2);

    while(!WindowShouldClose()) {
	ClearBackground(BLACK);
	BeginDrawing();
	EndDrawing();
    }
    CloseWindow();
    return 0;
}
