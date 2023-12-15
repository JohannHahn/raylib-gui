#pragma once

#include "raylib/src/raylib.h"

enum layout_type {
    VERTICAL, HORIZONTAL, LAYOUT_TYPE_MAX
};

class Layout {
public:
    Layout(Rectangle boundary, int type, int slot_count);
    Layout(int x, int y, int width, int height, int type, int slot_count);
    int get_slot_count();
    int get_item_count();
private:
    Rectangle boundary; 
    layout_type type;
    int slot_count;
    int items;
};
