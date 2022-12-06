#include "building-overlay.h"

#include "inputs.h"
#include "engine.h"


#include "example-bitmaps.h"
#include "collision.h"
#include "ui.h"

#include "timer.h"

// building that is going to be build
static const BuildingSpecification* buildTarget;


void buildingOverlaySelect(BuildingType building) {
	buildTarget = getSpec(building);
}

inline void drawBuildTarget() {
	al_draw_tinted_bitmap(buildTarget->bitmap, al_map_rgba_f(1.f, 1.f, 1.f, .5f), MOUSE_X, MOUSE_Y, 0);
}


void BuildingOverlay::draw() {
	const int n = 8;
	const int offset = 16;

	std::vector<ui::Image> items;
	for (int i = 0; i < n; i++)
		items.emplace_back(bitmap::square<64>(), 64, 64);
	
	if (!ui::drawBottomMenu(items, offset, CL_GREY)) {
		drawBuildTarget();
	}
}

