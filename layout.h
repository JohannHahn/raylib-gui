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
    Layout(Rectangle boundary, int type, int slot_count, float spacing = 0.f) 
    : boundary(boundary), type((layout_type)type), spacing(spacing){precompute_slots(slot_count);};
    Layout(float x, float y, float width, float height, int type, int slot_count, float spacing = 0.f) {Layout({x, y, width, height}, type, slot_count, spacing);};
    Layout(Rectangle boundary, int type, float slice_ratio, float spacing = 0.f);
    int get_slot_count() {return slot_list.size();};
    int get_type(){return type;}
    Rectangle get_slot(int slot, bool spaced = true);
    Rectangle get_boundary();
    static void center_rec(const Rectangle& boundary, Rectangle& to_center);
    static void print_rec(Rectangle rec);
    static void slice_rec(const Rectangle rec, float slice_ratio, int type, Rectangle& rec_out1, Rectangle& rec_out2);
    void set_spacing(float spacing);
    void draw();
    void resize(Rectangle new_boundary);
    void resize_from_point(Vector2 new_point);
    static Rectangle resize_rec(Rectangle rec, float new_x, float new_y, int type);
    float get_spacing();
    void resize_slots();
    void controls();
private:
    Rectangle boundary; 
    rec_list slot_list;
    layout_type type;
    //int current_slot = 0;
    float spacing = 0.f;
    float slice_ratio = 0.f;
    void precompute_slots(int slot_count);
    Rectangle get_default_slot_rec(int layout_type, int index, int slot_count);
};
