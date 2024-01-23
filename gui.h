#pragma once
#include "layout.h"
#include "raygui.h"
namespace Gui {
    struct Tree {

    };
    void table(Rectangle boundary, int num_cols, int num_rows, 
               const char* header_values, const char* body_values, void(*on_click)(void* data) = NULL); 
    bool tree_node(Rectangle boundary, const char* label, bool* open);
}
