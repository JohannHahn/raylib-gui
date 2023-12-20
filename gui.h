#pragma once

#include "raylib/src/raylib.h"
#include <assert.h>
#include <cstring>
#include <iostream>

namespace Gui {
bool Button(Rectangle rec, float spacing = 0.f, const char* label = "");
bool Slider(Rectangle rec, float min, float max, float& current, const char* label = "");
void center_rec(const Rectangle& boundary, Rectangle& to_center);
}
