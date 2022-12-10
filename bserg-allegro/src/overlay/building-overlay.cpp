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

bool anyBlockingTiles(World& world, Tile2 topLeftTile, Tile2 size) {
	for (int32_t y = 0; y < size.y; y++) {
		for (int32_t x = 0; x < size.x; x++) {
			Tile& tile = world.getTile(Tile2(x + topLeftTile.x, y + topLeftTile.y));
			if (tile.blocked)
				return true;
		}
	}
	return false;
}

void blockTiles(World& world, Tile2 topLeftTile, Tile2 size) {
	for (int32_t y = 0; y < size.y; y++) {
		for (int32_t x = 0; x < size.x; x++) {
			world.getTile(Tile2(x + topLeftTile.x, y + topLeftTile.y)).blocked = true;
		}
	}
}

// building that is going to be build
static BuildingType buildTarget;
// Offset from topleft to center
static Tile2 centerOffset; 

void buildingOverlaySelect(BuildingType buildingType) {
	buildTarget = buildingType;
	Tile2 size = getSpec(buildingType)->size;
	centerOffset = Tile2((size.x - 1) / 2, (size.y) / 2);
}

bool tryPlaceBuilding(World& world, Tile2 topLeftTile, uint8_t rotation, BuildingType buildingType) {
	const BuildingSpecification* spec = getSpec(buildingType);
	Tile2 rotatedSize = ROTATED_SIZE(rotation, spec->size);
	float angle = ROTATION_TO_ANGLE(rotation);

	// Try
	if (anyBlockingTiles(world, topLeftTile, rotatedSize))
		return false;

	blockTiles(world, topLeftTile, rotatedSize);

	// Place building into world
	world.buildings.emplace_back(buildingType, topLeftTile);

	return true;
}


void drawBuildingGhost (const BuildingSpecification* building, Tile2 topLeftTile, uint8_t rotation) {
	al_use_transform(&TRANSFORM_WORLD);

	// Make ghost red when blocked
	ALLEGRO_COLOR color = al_map_rgba_f(1.f, 1.f, 1.f, .6f);
	if (anyBlockingTiles(bserg::world, topLeftTile, building->size))
		color = al_map_rgba_f(1.f, .1f, .1f, .6f);
	
	// Draw ghost
	const Unit2 position(topLeftTile);
	const Unit2 centerPos(Tile2(0,0));		// Calculate the center somehow 
	drawBuilding(building->bitmap, building->size, topLeftTile, color);
}


void BuildingOverlay::draw() {
	const int n = BuildingType::COUNT;
	const int offset = 16;
	const BuildingSpecification* buildTargetSpecs = getSpec(buildTarget);
	
	float2 mouseCoords = float2(MOUSE_X, MOUSE_Y);
	al_transform_coordinates(&TRANSFORM_WORLD_INVERTED, &mouseCoords.x, &mouseCoords.y);
	
	const Tile2 mouseTile(Unit2(mouseCoords.x, mouseCoords.y));
	const Tile2 topLeftTile = mouseTile - centerOffset;

	std::vector<ui::Image> items;
	for (int i = 0; i < n; i++)
		items.emplace_back(bitmap::square<64>(), 64, 64);

	// Rotate in 4 parts
	static uint8_t rotation = 0;
	if (KEY_PRESSED(R))
		rotation = (rotation + 1) & 0b11;
	rotation = 0;
		

	int hit;
	if (ui::drawBottomMenu(items, offset, CL_GREY, hit)) {
		if (MOUSE_PRESSED(MOUSE_LEFT))
			buildingOverlaySelect((BuildingType)hit);

		return;
	}
	
	drawBuildingGhost(buildTargetSpecs, topLeftTile, rotation);
	
	if (MOUSE_PRESSED(MOUSE_LEFT)) {
		if (tryPlaceBuilding(bserg::world, topLeftTile, rotation, buildTarget)) {
			printf("I BUILD ANYWHERE\n");
		}
		else
		{
			printf("CANT BUILD HERE\n");
		}
	}
}

