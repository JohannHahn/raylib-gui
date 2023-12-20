#include "gui.h"
#include "raylib/src/raylib.h"

void Gui::center_rec(const Rectangle& boundary, Rectangle& to_center) {
    assert(boundary.width >= to_center.width && boundary.height >= to_center.height && "can't center with smaller boundary");
    to_center.x = boundary.x + boundary.width / 2.f - to_center.width / 2.f;
    to_center.y = boundary.y + boundary.height / 2.f - to_center.height / 2.f;
}

bool Gui::Button(Rectangle rec, float spacing, const char* label) {
    Rectangle text_rec;
    Vector2 mouse_pos = GetMousePosition();
    float line_thicc = (rec.width + rec.height) * 0.025f;
    float font_size = (rec.height - line_thicc) / (float)strlen(label) * 2.5f;
    bool released = IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_pos, rec);
    Vector2 font_dims = MeasureTextEx(GetFontDefault(), label, font_size, 0.f);

    text_rec.height = font_dims.y;
    text_rec.width = font_dims.x;
    center_rec(rec, text_rec);

    DrawRectangleRec(rec, GRAY);
    DrawRectangleLinesEx(rec, line_thicc, DARKGRAY);
    DrawText(label, text_rec.x - font_size / 2.f, text_rec.y, font_size, BLACK);

    return released;
}

bool Gui::Slider(Rectangle rec, float min, float max, float& current, const char* label) {
    Rectangle line_rec = rec;
    line_rec.height /= 5.f;
    center_rec(rec, line_rec);
    float circle_rad = line_rec.height / 2.f;
    Vector2 circle = {line_rec.x + current * line_rec.width, line_rec.y + line_rec.height / 2.f};
    Vector2 mouse_pos = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse_pos, line_rec);
    bool clicked = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

    if(hovered && clicked) {
	current = ((mouse_pos.x - line_rec.x) / line_rec.width) * max + min;
	if(current > line_rec.width) current = line_rec.width;
	else if(current < 0) current = 0;
	circle.x = line_rec.x + current * line_rec.width;
    }

    DrawRectangleRec(line_rec, GRAY);
    DrawCircle(circle.x, circle.y, circle_rad, BLACK);

    return hovered && clicked; 
}
