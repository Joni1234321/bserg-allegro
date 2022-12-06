#pragma once

#include "engine.h"

// Type
enum BuildingType {
	Storage,
	Barracks,

	// COUNT HAS TO BE LAST ELEMENT
	COUNT,	
};

// Properties
struct Building {
	BuildingType type;
	int2 topLeftPosition;
};




// Specs
struct BuildingSpecification {
public:
	ALLEGRO_BITMAP* bitmap;
	BuildingSpecification(ALLEGRO_COLOR color, int2 size) : bitmap(bitmapCreateTileRect(color, size)) {}
	BuildingSpecification() : BuildingSpecification(CL_ORANGE, int2(10, 10)) { }
	~BuildingSpecification() { al_destroy_bitmap(bitmap); }
};

void loadSpecs();
const BuildingSpecification* getSpec(BuildingType type);
