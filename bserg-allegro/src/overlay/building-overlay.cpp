#include "building-overlay.h"

#include "inputs.h"
#include "engine.h"
#include "example-bitmaps.h"


// building that is going to be build
static const BuildingSpecification* buildTarget;


void buildingOverlaySelect(BuildingType building) {
	buildTarget = getSpec(building);
}

inline void drawBuildTarget() {
	al_draw_tinted_bitmap(buildTarget->bitmap, al_map_rgba_f(1.f, 1.f, 1.f, .5f), MOUSE_X, MOUSE_Y, 0);
}

inline bool insideRect(int x, int y, int x1, int y1, int x2, int y2) {
	if (x >= x1 && x <= x2 && y >= y1 && y <= y2)
		return true;
	return false;
}

void BuildingOverlay::draw() {
	const int n = 5;
	const int offset = 50, dist = 40, width = 32;
	
	// Draw ui
	for (int i = 0; i < n; i++)
		al_draw_bitmap(SQUARE_BITMAP_32, offset + dist * i, offset, 0);


	int selectedUI = -1;
	// Check if hovering over button 
	for (int i = 0; i < n; i++) {
		int x1 = offset + dist * i;
		int x2 = x1 + width;
		int y1 = offset;
		int y2 = y1 + width;
		if (insideRect(MOUSE_X, MOUSE_Y, x1, y1, x2, y2)) {
			selectedUI = i; 
			return;
		}
	}

	// Draw build
	if (selectedUI == -1)
		drawBuildTarget();
}

