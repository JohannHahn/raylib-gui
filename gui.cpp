#include "gui.h"
#include "raylib/src/raylib.h"

const char* read_word(const char* words, int word) {
    int cursor = 0;
    int word_found = 0;
    while(word_found < word) {
	if(words[cursor] == '\0') {
	    word_found++;
	}
	cursor++;
    } 
    return words + cursor;
}
void Gui::table(Rectangle boundary, int num_rows, int num_cols, 
		const char* header_values, const char* body_values, float spacing, void(*on_click)(void* data)) {
    Layout table_layout = Layout(boundary, SLICE_VERT, 0.1f, spacing);
    Layout header = Layout(table_layout.get_slot(0), HORIZONTAL, num_cols, spacing);
    Layout row_layout = Layout(table_layout.get_slot(1), VERTICAL, num_rows, spacing);
    Color header_background_col = ColorAlpha(GRAY, 0.5f);

    for(int i = 0; i < num_cols; ++i) {
	Rectangle slot = header.get_slot(i);
	DrawRectangleRec(slot, header_background_col);
	GuiTextBox(slot, (char*)read_word(header_values, i), (int)(header.get_boundary().height), false);	
    }
    for(int i = 0; i < num_rows; ++i) {
	Layout single_row = Layout(row_layout.get_slot(i), HORIZONTAL, num_cols);
	int text_size = (int)(single_row.get_boundary().height);
	for(int j = 0; j < num_cols; ++j) {
	    Rectangle slot = single_row.get_slot(j);
	    char* word = (char*)read_word(body_values, j + i * num_cols);
	    if(on_click) {
		if(GuiLabelButton(slot, word)) {
		    on_click(word);
		}
	    }
	    else {
		GuiTextBox(slot, word, text_size, false);	
	    }
	    DrawLine(slot.x + slot.width, slot.y, slot.x + slot.width, slot.y + slot.height, BLACK);
	}
    }
    //header.draw();
    row_layout.draw();
}
