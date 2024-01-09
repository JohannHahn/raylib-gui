#include <math.h>
#include "layout.h"
#include "raylib/src/raylib.h"
#include "gui.h"

float window_width = 900;
float window_height = 600;
float controls_width = window_width / 4.f;
Rectangle main_window_boundary = {0, 0, window_width - controls_width, window_height};
Rectangle controls_boundary = {window_width - controls_width, 0, controls_width, window_height};
Layout control_layout = Layout(controls_boundary, SLICE_HOR, 0.1f);

void resize() {
    window_width = GetScreenWidth();
    window_height = GetScreenHeight();
    controls_width = window_width / 4.f;
    main_window_boundary = {0, 0, window_width - controls_width, window_height};
    controls_boundary = {window_width - controls_width, 0, controls_width, window_height};
    control_layout.resize(controls_boundary);
}

float vec_size(Vector2 vec) {
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
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
	Gui::table(main_window_boundary, 5, 5);
	EndDrawing();

    }
    CloseWindow();
    return 0;
}
