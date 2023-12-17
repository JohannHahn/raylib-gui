#include <iostream>
#include "layout.h"
#include "gui.h"

float window_width = 900;
float window_height = 600;
float controls_width = window_width / 4.f;
Rectangle main_window_boundary = {0, 0, window_width - controls_width, window_height};
Rectangle controls_boundary = {window_width - controls_width, 0, controls_width, window_height};
Layout control_layout = Layout(controls_boundary, VERTICAL, 5);

int main() {
    InitWindow(900, 600, "TEST");
    while(!WindowShouldClose()) {
	ClearBackground(BLACK);
	BeginDrawing();
	DrawRectangleRec(main_window_boundary, GREEN);
	if(Gui::Button(control_layout.next_slot(), "Button1")) {
	    std::cout << "hi\n";    
	}
	if(Gui::Button(control_layout.next_slot(), "Button2")) {
	    std::cout << "second button\n";    
	}
	EndDrawing();
    }
    CloseWindow();
    return 0;
}
