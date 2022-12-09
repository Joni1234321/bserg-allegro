#pragma once

#include "engine.h"

#include "colors.h"
#include "bitmap.h"

// Type
enum BuildingType {
	Storage,
	Barracks,
	Maintainance,
	Command,
	WorkerHousing,

	// COUNT HAS TO BE LAST ELEMENT
	COUNT,	
};


// Properties
struct Building {
	BuildingType type;
	Tile2 topLeftTile;
};




// Specs
struct BuildingSpecification {
public:
	ALLEGRO_BITMAP* bitmap;
	Tile2 size;
	BuildingSpecification(ALLEGRO_BITMAP* bitmap, Tile2 size) : bitmap(bitmap), size(size) { }
	BuildingSpecification(ALLEGRO_COLOR color, Tile2 size) : BuildingSpecification(bitmap::createRect(color, Unit2(size)), size) { }
	BuildingSpecification() : BuildingSpecification(CL_ORANGE, Tile2(10, 10)) { }
	~BuildingSpecification() { al_destroy_bitmap(bitmap); }
};

void loadSpecs();
Unit2 drawBuilding(ALLEGRO_BITMAP* bitmap, Tile2 size, Tile2 topLeftTile, ALLEGRO_COLOR color = al_map_rgb_f(1, 1, 1));
Unit2 drawBuilding(const Building& building);
const BuildingSpecification* getSpec(BuildingType type);
	