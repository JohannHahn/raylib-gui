#include <math.h>
#define GUI_IMPLEMENTATION
#include "gui.h"

float window_width = 900;
float window_height = 600;
float controls_width = window_width / 4.f;
Rectangle main_window_boundary = {0, 0, window_width - controls_width, window_height};
Rectangle controls_boundary = {window_width - controls_width, 0, controls_width, window_height};
Layout control_layout = Layout(controls_boundary, VERTICAL, 10);
Color bg_col = Color{0x18, 0x18, 0x18, 0xff};

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

void on_click(void* data) {
    const char* label = (const char*) data;
    std::cout << "clicked button " << label << "\n";
}

int main() {
    control_layout.set_spacing(10);
    InitWindow(900, 600, "TEST");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTraceLogLevel(LOG_ERROR | LOG_WARNING);
    const char* header = "one\0two\0three";
    const char* body = "one\0two\0three\0four\0five\0six\0seven\0eight\0nine";
    resize();
    while(!WindowShouldClose()) {
	if(IsWindowResized()) {
	    resize();
	}
	ClearBackground(bg_col);
	Gui::table(main_window_boundary, 3, 3, header, body, on_click); 
	Gui::begin_tree(controls_boundary);
	if(Gui::tree_node("tree node")) {
	    Gui::tree_node("tree leaf");
	    Gui::tree_pop();
	}
	Gui::end_tree();
	EndDrawing();

    }
    CloseWindow();
    return 0;
}
