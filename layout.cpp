#define RAYGUI_IMPLEMENTATION
#include "layout.h"

Rectangle Layout::get_slot(int slot_index, bool spaced) {
    slot_index %= slot_count;
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
