#include "gui.h"
#include "../data_base.h"
#include <unordered_map>
#include "raylib/src/raylib.h"

Gui::Node tree;
Gui::Node* tree_head;
Layout tree_layout = Layout({0}, VERTICAL, 0);
std::vector<Rectangle> tree_stack;
std::unordered_map<std::string, bool> tree_state;
int tree_node_count = 0;

bool contains(const std::unordered_map<std::string, bool>& map, const char* key) {
    for(std::pair<std::string, bool> pair : map) {
	if(pair.first == key) return true;
    }
    return false;
}

const char* Gui::read_word(const char* words, int word) {
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

void Gui::begin_tree(Rectangle boundary) {
    tree_layout = Layout(boundary, VERTICAL, 10);
    tree_stack.push_back({0});
    tree_node_count = 0;
}

void Gui::end_tree() {
    tree_stack.clear();
}


Rectangle scale_node_boundary(Rectangle parent_boundary) {
    if(parent_boundary.width == 0) return tree_layout.get_slot(0);
    float scale_factor = 0.9f;
    float new_width = parent_boundary.width * scale_factor;
    float new_x = parent_boundary.x + parent_boundary.width - new_width; 
    parent_boundary.x = new_x; parent_boundary.width = new_width;
    parent_boundary.y = parent_boundary.height * (tree_node_count - 1);
    return parent_boundary;
}

void Gui::tree_push(const char* label) {
    tree_state[label] = false;
}
void Gui::tree_pop() {
    tree_stack.pop_back();
}
bool Gui::tree_node(const char *label) {
    tree_node_count++;
    if(!contains(tree_state, label)) {
	tree_state[label] = false;
    }

    Rectangle parent_boundary = tree_stack[tree_stack.size() - 1];
    Rectangle boundary = scale_node_boundary(parent_boundary);
    Layout node_layout = Layout(boundary, SLICE_HOR, 0.1f);
    bool open = tree_state[label];
    const char* toggle_label = open ? "^" : ">";

    GuiToggle(node_layout.get_slot(0), toggle_label, &open);
    tree_state[label] = open;

    if(GuiButton(node_layout.get_slot(1), label)) {
	std::cout << label << "\n";
    }

    tree_stack.push_back(boundary);
    return open;
}


