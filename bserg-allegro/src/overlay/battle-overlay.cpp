#include "battle-overlay.h"

#include <allegro5/display.h>
#include <allegro5/allegro_primitives.h>

#include "transforms.h"
#include "inputs.h"
#include "colors.h"


static ALLEGRO_TRANSFORM battleTransform, battleTransformInverted;

// Obectvies in each side
static const uint32_t layers = 4, layerHeight = 5, objectivesPerLayer = 2;

static const uint32_t mapH = layerHeight * UNITS_PER_TILE, mapW = (layers * 2 + 1) * UNITS_PER_TILE;


static void drawObjective(Objective objective) {
	int size = 3;
	ALLEGRO_COLOR color = CL_BLACK;

	if (objective.contested) {
		size = 5;
		color = CL_RED;
	}

	al_draw_filled_circle(objective.position.x, objective.position.y, size, color);
}

static bool exists(uint32_t test, const uint32_t *ar, uint32_t length) {
	for (uint32_t i = 0; i < length; i++)
		if (ar[i] == test)
			return true;
	return false;
}
static uint32_t * generateUnique(uint32_t height, uint32_t amount) {
	assert(amount <= height);
	uint32_t* re = new uint32_t[amount];
	for (uint32_t i = 0; i < amount; i++) {
		uint32_t test;
		do
			test = rand() % layerHeight;
		while (exists(test, re, i));
		re[i] = test;
	}

	return re;
}
// 300 600
// 100 700
BattleOverlay::BattleOverlay() {
	al_identity_transform(&battleTransform);

	objectives = new Objective[objectivesPerLayer * (layers * 2 + 1)];
	neighbors = new uint32_t[objectivesPerLayer * (layers * 2 + 1)];
	// Draw map
	for (size_t layer = 0; layer < layers; layer++)
	{
		// For each layer
		uint32_t* tilePositions = generateUnique(layerHeight, objectivesPerLayer);
		
		for (size_t i = 0; i < objectivesPerLayer; i++) {
;			int2 pos(UNITS_PER_TILE * (layer + .5f), UNITS_PER_TILE * (tilePositions[i] + .5f));
			objectives[layer * objectivesPerLayer + i] = Objective(int2(pos.x, pos.y), false);
			objectives[(layers * 2 - layer + 1) * objectivesPerLayer + i] = Objective(int2(mapW - pos.x, pos.y), false);
		}
	}

	uint32_t* tilePositions = generateUnique(layerHeight, objectivesPerLayer);
	for (size_t i = 0; i < objectivesPerLayer * 2; i++) {
		int2 pos(UNITS_PER_TILE *(layers + .5f), UNITS_PER_TILE * (tilePositions[i] + .5f));
		objectives[layers * layerHeight + i] = Objective(pos, true);
	}

}

void BattleOverlay::draw() {
	al_copy_transform(&battleTransformInverted, &battleTransform);
	al_invert_transform(&battleTransformInverted);
	al_use_transform(&battleTransform);

	static const int2 start(0, 0);


	float2 mouseCoords = float2(MOUSE_X, MOUSE_Y);
	al_transform_coordinates(&battleTransformInverted, &mouseCoords.x, &mouseCoords.y);
	const Tile2 mouseTile(Unit2(mouseCoords.x, mouseCoords.y));
	const Unit2 snappedMouse(mouseTile);

	al_draw_filled_rectangle(start.x, start.y, mapW, mapH, CL_GREY);
	al_hold_bitmap_drawing(true);
	
	for (size_t i = 0; i < layers; i++) {
		drawObjective(objectives[i]);
	}

	al_hold_bitmap_drawing(false);
	
	al_draw_rectangle(snappedMouse.x, snappedMouse.y, snappedMouse.x + UNITS_PER_TILE, snappedMouse.y + UNITS_PER_TILE, CL_ORANGE, 2);
}