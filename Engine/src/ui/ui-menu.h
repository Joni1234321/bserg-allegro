#pragma once
#include "ui-types.h"

#include <vector>

namespace ui {
	// A menu consists of items 
	bool drawBottomMenu(std::vector<Image> items, int offset, ALLEGRO_COLOR background, int& out, int paddingX = 10, int paddingY = 10);
}