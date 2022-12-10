#include "battle-overlay.h"

#include <allegro5/display.h>
#include <allegro5/allegro_primitives.h>

#include "colors.h"



// Obectvies in each side
static const uint32_t mapW = 600, mapH = 300;


static void drawObjective(Objective objective) {
	int size = 3;
	ALLEGRO_COLOR color = CL_BLACK;

	if (objective.contested) {
		size = 5;
		color = CL_RED;
	}

	al_draw_filled_circle(objective.position.x, objective.position.y, size, color);
}

// 300 600
// 100 700
BattleOverlay::BattleOverlay() {
	// Draw map
	const size_t n = 5;
	for (size_t i = 0; i < n; i++) {
		int2 pos(rand() % (mapW / 2), rand() % mapH);
		objectives.emplace_back(int2(pos.x, pos.y), false);
		objectives.emplace_back(int2(mapW - pos.x, pos.y), false);
	}
}

void BattleOverlay::draw() {
	static const int2 start(0, 0);
	al_draw_filled_rectangle(start.x, start.y, mapW, mapH, CL_GREY);
	al_hold_bitmap_drawing(true);
	
	const size_t n = objectives.size();
	for (size_t i = 0; i < n; i++) {
		drawObjective(objectives[i]);
	}

	al_hold_bitmap_drawing(false);
	
}