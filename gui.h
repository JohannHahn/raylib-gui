#pragma once
#include "layout.h"
#include "raygui.h"
#include <vector>
namespace Gui {
    struct Node;
    typedef std::vector<Node> node_list;
    struct Node{
        bool* open;
        Rectangle boundary;
        const char* label;
        node_list children;
        Node* parent;
    };

    void table(Rectangle boundary, int num_cols, int num_rows, 
               const char* header_values, const char* body_values, void(*on_click)(void* data) = NULL); 
    void begin_tree(Rectangle boundary);
    void end_tree();
    bool tree_node(const char* label, bool default_open = false, bool* button_click = NULL);
    void tree_push(const char* label, bool open);
    void tree_pop();
    void draw_tree(Node* head, int depth = 0);
    const char* read_word(const char* words, int word);
}
