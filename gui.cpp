#include "gui.h"
#include "raylib/src/raylib.h"

Gui::Node tree;
Gui::Node* tree_head;

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

void Gui::table(Rectangle boundary, int num_cols, int num_rows, 
		const char* header_values, const char* body_values, void(*on_click)(void* data)) {
    Layout table_layout = Layout(boundary, SLICE_VERT, 0.1f);
    Layout header = Layout(table_layout.get_slot(0), HORIZONTAL, num_cols);
    Layout row_layout = Layout(table_layout.get_slot(1), VERTICAL, num_rows);
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

void Gui::begin_tree() {
    tree_head = &tree; 
}

void Gui::end_tree() {
    draw_tree(&tree);
    tree.children.clear();
}

Rectangle scale_node_boundary(Rectangle boundary, int depth) {
    if(depth == 0) return boundary;
    float scale_factor = 0.75f / (float)depth;
    float new_width = boundary.width * scale_factor;
    float new_x = boundary.x + boundary.width - new_width; 
    Rectangle bs = boundary;
    bs.x = new_x; bs.width = new_width;
    return bs;
}

void Gui::draw_tree(Node* head, int depth) {
    if(!head) return;
    for(Node n : head->children) {
	n.boundary = scale_node_boundary(n.boundary, depth);
	const char* toggle_label = *n.open ? "^" : ">";
	Layout node_layout = Layout(n.boundary, SLICE_HOR, 0.1f);
	GuiToggle(node_layout.get_slot(0), toggle_label, n.open);
	if(GuiButton(node_layout.get_slot(1), n.label)) {
	    std::cout << n.label << "\n";
	}
	draw_tree(&n, depth + 1);
    }
}

void Gui::tree_node(Rectangle boundary, const char *label, bool* open) {
    Node node = {.open = open, .boundary = boundary, .label = label};
    tree_head->children.push_back(node);
    tree_head = &tree_head->children[tree_head->children.size() - 1];
}


