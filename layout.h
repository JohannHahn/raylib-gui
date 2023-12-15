#pragma once

enum layout_type {
    VERTICAL, HORIZONTAL, LAYOUT_TYPE_MAX
};

struct Rectangle {
    int x;
    int y;
    int width;
    int height;
};

class Layout {
public:
    Layout(Rectangle boundary, layout_type type, int slot_count);
    Layout(int x, int y, int width, int height, layout_type type, int slot_count);
    int get_slot_count();
    int get_item_count();
private:
    Rectangle boundary; 
    layout_type type;
    int slot_count;
    int items;
};
