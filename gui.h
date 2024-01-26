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
    };

    void table(Rectangle boundary, int num_cols, int num_rows, 
               const char* header_values, const char* body_values, void(*on_click)(void* data) = NULL); 
    void begin_tree();
    void end_tree();
    void tree_node(Rectangle boundary, const char* label, bool* open);
    void draw_tree(Node* head, int depth = 0);
}
