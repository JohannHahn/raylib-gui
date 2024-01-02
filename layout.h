#pragma once

#include "raygui.h"
#include <iostream>
#include <assert.h>
#include <vector> 

typedef std::vector<Rectangle> rec_list;
enum layout_type {
    VERTICAL, HORIZONTAL, SLICE_VERT, SLICE_HOR, LAYOUT_TYPE_MAX
};

class Layout {
public:
    Layout(Rectangle boundary, int type, int slot_count) 
    : boundary(boundary), type((layout_type)type), slot_count(slot_count){precompute_slots();};
    Layout(float x, float y, float width, float height, int type, int slot_count) {Layout({x, y, width, height}, type, slot_count);};
    int get_slot_count();
    int get_type(){return type;}
    Rectangle get_default_slot_rec(int layout_type, int index);
    Rectangle get_slot(int slot, bool spaced = true);
    Rectangle get_boundary();
    static void center_rec(const Rectangle& boundary, Rectangle& to_center);
    static void print_rec(Rectangle rec);
    void set_spacing(float spacing);
    void draw();
    void resize(Rectangle boundary);
    static Rectangle resize_rec(Rectangle rec, float new_x, float new_y, int type);
    float get_spacing();
    void precompute_slots();
    void resize_slots();
    void controls();
private:
    Rectangle boundary; 
    rec_list slot_list;
    layout_type type;
    int slot_count;
    int current_slot = 0;
    float spacing = 0.f;
};
