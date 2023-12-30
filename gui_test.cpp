#include "layout.h"

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
    control_layout.resize(controls_boundary);
}

int main() {
    control_layout.set_spacing(10);
    InitWindow(900, 600, "TEST");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTraceLogLevel(LOG_ERROR | LOG_WARNING);
    float value = 0;
    bool focused = false;
    std::string buffer;
    resize();
    std::cout << "spacing = " << control_layout.get_spacing() << "\n";
    while(!WindowShouldClose()) {
	if(IsWindowResized()) {
	    resize();
	}
	ClearBackground(YELLOW);
	for(int slot = 0; slot < control_layout.get_slot_count(); ++slot) {
	    if(GuiButton(control_layout.get_slot(slot), TextFormat("%d", slot))) {
		std::cout << slot <<"\n";
	    }
	}
	control_layout.draw();
	EndDrawing();

    }
    CloseWindow();
    return 0;
}
