#include "layout.h"
#include <assert.h>

Rectangle Layout::next_slot() {
    Rectangle slot;
    switch (type) {
    case VERTICAL:
	slot.x = boundary.x;
	slot.y = boundary.y / (float)slot_count * (float)current_slot;
	slot.width = boundary.width;
	slot.height = boundary.height / (float)slot_count;
	break;
    case HORIZONTAL:
	slot.x = boundary.x / (float)slot_count * (float)current_slot;
	slot.y = boundary.y;
	slot.width = boundary.width / (float)slot_count;
	slot.height = boundary.height;
	break;
    case LAYOUT_TYPE_MAX:
	assert(false && "unreachable");
	break;
    }
    current_slot++;
    return slot;
}
