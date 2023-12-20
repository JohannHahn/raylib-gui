#include <iostream>
#include "layout.h"
#include "gui.h"

float window_width = 900;
float window_height = 600;
float controls_width = window_width / 4.f;
Rectangle main_window_boundary = {0, 0, window_width - controls_width, window_height};
Rectangle controls_boundary = {window_width - controls_width, 0, controls_width, window_height};
Layout control_layout = Layout(controls_boundary, VERTICAL, 5);

void resize() {
    window_width = GetScreenWidth();
    window_height = GetScreenHeight();
    controls_width = window_width / 4.f;
    main_window_boundary = {0, 0, window_width - controls_width, window_height};
    controls_boundary = {window_width - controls_width, 0, controls_width, window_height};
    control_layout = Layout(controls_boundary, VERTICAL, 5);
}

int main() {
    control_layout.set_spacing(5);
    InitWindow(900, 600, "TEST");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    float value = 0;
    while(!WindowShouldClose()) {
	resize();
	ClearBackground(YELLOW);
	BeginDrawing();
	for(int i = 0; i < 4; ++i) {
	    if(Gui::Button(control_layout.get_slot(i), 0.f, TextFormat("Button %d", i))) {
		std::cout << "Hi i am button " << i << "\n";
	    }
	}
	if(Gui::Slider(control_layout.get_slot(4), 0, 1, value, "Slidör")) {
	}
	EndDrawing();
    }
    CloseWindow();
    return 0;
}
