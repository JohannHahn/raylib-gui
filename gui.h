#pragma once

#include "raylib/src/raylib.h"
#include <cstring>

namespace Gui {

bool Button(Rectangle rec, float spacing = 0.f, const char* label = "");
bool Slider(Rectangle rec, float min, float max, float& current, const char* label = "");
};
