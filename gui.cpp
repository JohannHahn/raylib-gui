#include "gui.h"
#include "raylib/src/raylib.h"

void Gui::table(Rectangle boundary, int num_rows, int num_cols, float spacing) {
    Layout table_layout = Layout(boundary, SLICE_VERT, 0.1f, spacing);
    Layout header = Layout(table_layout.get_slot(0), HORIZONTAL, num_cols, spacing);
    Layout row_layout = Layout(table_layout.get_slot(1), VERTICAL, num_rows, spacing);
    Color header_background_col = ColorAlpha(GRAY, 0.5f);
    for(int i = 0; i < num_cols; ++i) {
	Rectangle slot = header.get_slot(i);
	DrawRectangleRec(slot, header_background_col);
	GuiTextBox(slot, (char*)TextFormat("%d", i), (int)(header.get_boundary().height), false);	
    }
    for(int i = 0; i < num_rows; ++i) {
	Layout single_row = Layout(row_layout.get_slot(i), HORIZONTAL, num_cols);
	for(int j = 0; j < num_cols; ++j) {
	    GuiTextBox(single_row.get_slot(j), (char*)TextFormat("%d", i*j), (int)(single_row.get_boundary().height), false);	
	}
    }
    header.draw();
    row_layout.draw();
}
