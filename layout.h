#pragma once

#include "raylib/src/raylib.h"

enum layout_type {
    VERTICAL, HORIZONTAL, LAYOUT_TYPE_MAX
};

class Layout {
public:
    Layout(Rectangle boundary, int type, int slot_count) : boundary(boundary), type((layout_type)type), slot_count(slot_count){};
    Layout(float x, float y, float width, float height, int type, int slot_count) {Layout({x, y, width, height}, type, slot_count);};
    int get_slot_count();
    bool is_occupied(int slot);
    Rectangle next_slot();
private:
    Rectangle boundary; 
    layout_type type;
    int slot_count;
    int current_slot = 0;
};
