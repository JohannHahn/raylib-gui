#pragma once
#include "layout.h"
#include "raygui.h"
namespace Gui {
    void table(Rectangle boundary, int num_rows, int num_cols, 
               const char* header_values, const char* body_values, float spacing = 0.f); 
}
