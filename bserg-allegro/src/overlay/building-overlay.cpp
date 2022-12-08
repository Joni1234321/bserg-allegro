#include "building-overlay.h"

#include <allegro5/bitmap_draw.h>

#include "bserg.h"

#include "inputs.h"
#include "globals.h"
#include "engine.h"

#include "bitmap.h"
#include "collision.h"
#include "transforms.h"
#include "ui.h"

#include "timer.h"

bool anyBlockingTiles(World& world, int2 topLeftTile, int2 size) {
	for (int y = 0; y < size.y; y++) {
		for (int x = 0; x < size.x; x++) {
			Tile& tile = world.getTile(int2(x + topLeftTile.x, y + topLeftTile.y));
			if (tile.blocked)
				return true;
		}
	}
	return false;
}

void blockTiles(World& world, int2 topLeftTile, int2 size) {
	for (int y = 0; y < size.y; y++) {
		for (int x = 0; x < size.x; x++) {
			world.getTile(int2(x + topLeftTile.x, y + topLeftTile.y)).blocked = true;
		}
	}
}

// building that is going to be build
static BuildingType buildTarget;
// Offset from topleft to center
static int2 centerTileOffset; 

void buildingOverlaySelect(BuildingType buildingType) {
	buildTarget = buildingType;
	int2 size = getSpec(buildingType)->size;
	centerTileOffset = int2((size.x - 1) / 2, (size.y) / 2);
}

bool tryPlaceBuilding(World& world, int2 topLeftTile, BuildingType buildingType) {
	const BuildingSpecification* spec = getSpec(buildingType);
	// Try
	if (anyBlockingTiles(world, topLeftTile, spec->size))
		return false;

	blockTiles(world, topLeftTile, spec->size);

	// Place building into world
	world.buildings.emplace_back(buildingType, topLeftTile);

	return true;
}


void drawBuildingGhost (const BuildingSpecification* building, int2 topLeftTile) {
	al_use_transform(&TRANSFORM_WORLD);
	// Make ghost red when blocked
	ALLEGRO_COLOR color = al_map_rgba_f(1.f, 1.f, 1.f, .6f);
	if (anyBlockingTiles(bserg::world, topLeftTile, building->size))
		color = al_map_rgba_f(1.f, .1f, .1f, .6f);
	
	// Draw ghost
	const int2 pos = TILE_TO_UNIT(topLeftTile);
	al_draw_tinted_bitmap(building->bitmap, color, pos.x, pos.y, 0);
}


void BuildingOverlay::draw() {
	const int n = BuildingType::COUNT;
	const int offset = 16;
	const BuildingSpecification* buildTargetSpecs = getSpec(buildTarget);
	
	float2 mouseCoords = float2(MOUSE_X, MOUSE_Y);
	al_transform_coordinates(&TRANSFORM_WORLD, &mouseCoords.x, &mouseCoords.y);
	
	const int2 mouseTile = UNIT_TO_TILE(int2(mouseCoords.x, mouseCoords.y));
	const int2 topLeftTile = mouseTile - centerTileOffset;

	std::vector<ui::Image> items;
	for (int i = 0; i < n; i++)
		items.emplace_back(bitmap::square<64>(), 64, 64);

	int hit;
	if (ui::drawBottomMenu(items, offset, CL_GREY, hit)) {
		if (MOUSE_PRESSED(MOUSE_LEFT))
			buildingOverlaySelect((BuildingType)hit);

		return;
	}
	
	drawBuildingGhost(buildTargetSpecs, topLeftTile);
	
	if (MOUSE_PRESSED(MOUSE_LEFT)) {
		if (tryPlaceBuilding(bserg::world, topLeftTile, buildTarget)) {
			printf("I BUILD ANYWHERE\n");
		}
		else
		{
			printf("CANT BUILD HERE\n");
		}
	}
}

