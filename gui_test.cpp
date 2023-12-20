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
    control_layout.set_spacing(50);
    InitWindow(900, 600, "TEST");
    while(!WindowShouldClose()) {
	ClearBackground(YELLOW);
	BeginDrawing();
	for(int i = 0; i < 4; ++i) {
	    if(Gui::Button(control_layout.get_slot(i), 0.f, TextFormat("Button %d", i))) {
		std::cout << "Hi i am button " << i << "\n";
	    }
	}
	float value = 0;
	if(Gui::Slider(control_layout.get_slot(4), 0, 1, value, "Slidör")) {
	    std::cout << "sliding = " << value << "\n";
	}
	EndDrawing();
    }
    CloseWindow();
    return 0;
}
