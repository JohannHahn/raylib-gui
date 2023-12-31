#define RAYGUI_IMPLEMENTATION
#include "layout.h"

void Layout::resize_slots() {
    assert(slot_list.size() == slot_count && "slot count != size of slot_list");
    for(int slot_index = 0; slot_index < slot_list.size(); ++slot_index) {
	switch (type) {
	case VERTICAL:
	    slot_list[slot_index].x = boundary.x;
	    slot_list[slot_index].y = (boundary.height / (float)slot_count) * (float)slot_index;
	    slot_list[slot_index].width = boundary.width;
	    slot_list[slot_index].height = boundary.height / (float)slot_count;
	    break;
	case HORIZONTAL:
	    slot_list[slot_index].x = boundary.width / (float)slot_count * (float)slot_index;
	    slot_list[slot_index].y = boundary.y;
	    slot_list[slot_index].width = boundary.width / (float)slot_count;
	    slot_list[slot_index].height = boundary.height;
	    break;
	case LAYOUT_TYPE_MAX:
	    assert(false && "unreachable");
	    break;
	}
    }
}
void Layout::precompute_slots() {
    for(int slot_index = 0; slot_index < slot_count; ++slot_index) {
	Rectangle slot;
	switch (type) {
	case VERTICAL:
	    slot.x = boundary.x;
	    slot.y = (boundary.height / (float)slot_count) * (float)slot_index;
	    slot.width = boundary.width;
	    slot.height = boundary.height / (float)slot_count;
	    break;
	case HORIZONTAL:
	    slot.x = boundary.width / (float)slot_count * (float)slot_index;
	    slot.y = boundary.y;
	    slot.width = boundary.width / (float)slot_count;
	    slot.height = boundary.height;
	    break;
	case LAYOUT_TYPE_MAX:
	    assert(false && "unreachable");
	    break;
	}
	slot_list.push_back(slot);
    }
    assert(slot_list.size() == slot_count && "slot count != size of slot_list");

}
Rectangle Layout::get_slot(int slot_index, bool spaced) {
    slot_index %= slot_count;
    assert(slot_index < slot_list.size());
    Rectangle slot = slot_list[slot_index];
    if(spaced) {
	Rectangle slot_nospace = slot;
	slot.width -= spacing * 2.f;
	slot.height -= spacing * 2.f;
	center_rec(slot_nospace, slot);
    }
    return slot;
}

void Layout::resize(Rectangle boundary) {
    this->boundary = boundary;
    resize_slots();
}

Rectangle Layout::get_boundary() {
    return boundary;
}

Rectangle Layout::resize_rec(Rectangle rec, float new_x, float new_y, int type) {
    if(type == VERTICAL) {
	rec.width -= new_x - rec.x;
    }
    else if(type == HORIZONTAL) {
	rec.height -= new_y - rec.y;
    }
    rec.x = new_x;
    rec.y = new_y;
    return rec;
}

void Layout::center_rec(const Rectangle& boundary, Rectangle& to_center) {
    assert(boundary.width >= to_center.width && boundary.height >= to_center.height && "can't center with smaller boundary");
    to_center.x = boundary.x + boundary.width / 2.f - to_center.width / 2.f;
    to_center.y = boundary.y + boundary.height / 2.f - to_center.height / 2.f;
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
    for(int slot = 0; slot < slot_count; ++slot) {
	//GuiGroupBox(get_slot(slot), "");
	DrawRectangleLinesEx(get_slot(slot, false), 1, BLACK);
    }
}

int Layout::get_slot_count() {
    return slot_count;
}
