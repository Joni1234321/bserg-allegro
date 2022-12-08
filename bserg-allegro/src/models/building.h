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

	// COUNT HAS TO BE LAST ELEMENT
	COUNT,	
};

// Properties
struct Building {
	BuildingType type;
	int2 topLeftTile;
};




// Specs
struct BuildingSpecification {
public:
	ALLEGRO_BITMAP* bitmap;
	int2 size;
	BuildingSpecification(ALLEGRO_COLOR color, int2 size) : bitmap(bitmap::createTileRect(color, size)), size(size) {}
	BuildingSpecification() : BuildingSpecification(CL_ORANGE, int2(10, 10)) { }
	~BuildingSpecification() { al_destroy_bitmap(bitmap); }
};

void loadSpecs();
const BuildingSpecification* getSpec(BuildingType type);
