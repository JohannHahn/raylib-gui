#define RAYGUI_IMPLEMENTATION
#include "layout.h"

Layout::Layout(Rectangle boundary, int type, float slice_ratio) 
    :boundary(boundary), type((layout_type)type), slice_ratio(slice_ratio) {
    assert(type > HORIZONTAL && "this constructor is for slice types");
    Rectangle rec1, rec2;
    slice_rec(boundary, slice_ratio, type, rec1, rec2);
    print_rec(boundary);
    print_rec(rec1);
    print_rec(rec2);
    slot_list.push_back(rec1);
    slot_list.push_back(rec2);
}

void Layout::resize_slots() {
    if(type < SLICE_VERT) {
	int slot_count = slot_list.size();
	for(int slot_index = 0; slot_index < slot_list.size(); ++slot_index) {
	    slot_list[slot_index] = get_default_slot_rec(type, slot_index, slot_count);
	}
    }
    else {
	slice_rec(boundary, slice_ratio, type, slot_list[0], slot_list[1]);
    }
    
}
Rectangle Layout::get_default_slot_rec(int layout_type, int slot_index, int slot_count) {
    Rectangle slot;
	switch (layout_type) {
	case VERTICAL:
	    slot.x = boundary.x;
	    slot.y = boundary.y + (boundary.height / (float)slot_count) * (float)slot_index;
	    slot.width = boundary.width;
	    slot.height = boundary.height / (float)slot_count;
	    break;
	case HORIZONTAL:
	    slot.x = boundary.x + boundary.width / (float)slot_count * (float)slot_index;
	    slot.y = boundary.y;
	    slot.width = boundary.width / (float)slot_count;
	    slot.height = boundary.height;
	    break;
	case SLICE_VERT:
	case SLICE_HOR:
	case LAYOUT_TYPE_MAX:
	    assert(false && "unreachable");
	    break;
	}
    return slot;
}
void Layout::precompute_slots(int slot_count) {
    for(int slot_index = 0; slot_index < slot_count; ++slot_index) {
	Rectangle slot = get_default_slot_rec(type, slot_index, slot_count);
	slot_list.push_back(slot);
    }

}
Rectangle Layout::get_slot(int slot_index, bool spaced) {
    slot_index %= slot_list.size();
    Rectangle slot = slot_list[slot_index];
    if(spaced) {
	Rectangle slot_nospace = slot;
	slot.width -= spacing * 2.f;
	slot.height -= spacing * 2.f;
	center_rec(slot_nospace, slot);
    }
    return slot;
}

void Layout::resize(Rectangle new_boundary) {
    boundary = new_boundary;
    resize_slots();
}
void Layout::resize_from_point(Vector2 new_point) {
    Rectangle new_boundary = resize_rec(boundary, new_point.x, new_point.y, type);
    resize(new_boundary);
}

Rectangle Layout::get_boundary() {
    return boundary;
}

Rectangle Layout::resize_rec(Rectangle rec, float new_x, float new_y, int type) {
    if(type == VERTICAL) {
	rec.width -= new_x - rec.x;
	rec.x = new_x;
    }
    else if(type == HORIZONTAL) {
	rec.height -= new_y - rec.y;
	rec.y = new_y;
    }
    return rec;
}

void Layout::center_rec(const Rectangle& boundary, Rectangle& to_center) {
    to_center.x = boundary.x + boundary.width / 2.f - to_center.width / 2.f;
    to_center.y = boundary.y + boundary.height / 2.f - to_center.height / 2.f;
}

void Layout::slice_rec(const Rectangle rec, float slice_ratio, int type, Rectangle& out1, Rectangle& out2) {
    assert(type > HORIZONTAL);
    float width = type == SLICE_VERT ? rec.width : rec.width * slice_ratio;
    float height = type == SLICE_HOR ? rec.height : rec.height * slice_ratio;
    out1 = Rectangle{rec.x, rec.y, width, height};

    float x2 = type == SLICE_VERT ? out1.x : out1.x + width;
    float y2 = type == SLICE_HOR ? out1.y : out1.y + height;
    float width2 = type == SLICE_VERT ? rec.width : rec.width * (1.f - slice_ratio);
    float height2 = type == SLICE_HOR ? rec.height : rec.height * (1.f - slice_ratio);
    out2 = Rectangle{x2, y2, width2, height2};
}

void Layout::set_spacing(float spacing) {
    this->spacing = spacing;
}
float Layout::get_spacing() {
    return spacing;
}

void Layout::print_rec(Rectangle rec) {
    std::cout << "rectangle: x = " << rec.x << ", y = " << rec.y 
	<< ", width = " << rec.width << ", height = " << rec.height << "\n";
}

void Layout::draw() {
    int slot_count = slot_list.size();
    for(int slot = 0; slot < slot_count; ++slot) {
	//GuiGroupBox(get_slot(slot), "");
	DrawRectangleLinesEx(get_slot(slot, false), 1, BLACK);
    }
}
