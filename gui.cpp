#include "gui.h"
#include "raylib/src/raylib.h"

bool Gui::Button(Rectangle rec, const char* label) {
    DrawRectangleRec(rec, GRAY);
    Vector2 mouse_pos = GetMousePosition();
    float font_size = rec.height / 2.f;
    float text_size = MeasureText(label, font_size);
    DrawText(label, rec.x + text_size / font_size, rec.y + font_size / 2.f, font_size, BLACK);
    bool click = IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_pos, rec);
    return click;
}
