#pragma once

#include "raygui.h"
#include <iostream>
#include <assert.h>

enum layout_type {
    VERTICAL, HORIZONTAL, SLICE_VERT, SLICE_HOR, LAYOUT_TYPE_MAX
};

class Layout {
public:
    Layout(Rectangle boundary, int type, int slot_count) : boundary(boundary), type((layout_type)type), slot_count(slot_count){};
    Layout(float x, float y, float width, float height, int type, int slot_count) {Layout({x, y, width, height}, type, slot_count);};
    int get_slot_count();
    // slot gets clamped to 0 - slot_count
    Rectangle get_slot(int slot);
    static void center_rec(const Rectangle& boundary, Rectangle& to_center);
    static void print_rec(Rectangle rec);
    void set_spacing(float spacing);
    void draw();
private:
    Rectangle boundary; 
    layout_type type;
    int slot_count;
    int current_slot = 0;
    float spacing = 0.f;
};
