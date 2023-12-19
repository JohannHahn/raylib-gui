#include "gui.h"


bool Gui::Button(Rectangle rec, float spacing, const char* label) {
    Vector2 mouse_pos = GetMousePosition();
    float line_thicc = (rec.width + rec.height) * 0.025f;
    float font_size = (rec.height - line_thicc) / (float)strlen(label) * 2.5f;
    Vector2 font_dims = MeasureTextEx(GetFontDefault(), label, font_size, 0.f);
    bool released = IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_pos, rec);
    // center horizontally
    float text_x = (rec.x + rec.width / 2.f) - font_dims.x / 1.9f;
    // center vertically 
    float text_y = (rec.y + rec.height / 2.f) - font_dims.y / 2.f;

    DrawRectangleRec(rec, GRAY);
    DrawRectangleLinesEx(rec, line_thicc, WHITE);
    DrawText(label, text_x, text_y, font_size, BLACK);

    return released;
}

bool Gui::Slider(Rectangle rec, float min, float max, float& current, const char* label) {
    Rectangle line_rec = rec;
    line_rec.height /= 5.f;
    Vector2 mouse_pos = GetMousePosition();
    bool released = IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_pos, line_rec);
    DrawRectangleRec(line_rec, WHITE);
    return released; 
}
