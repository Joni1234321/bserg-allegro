#pragma once

#include "engine.h"

#include "models/building.h"
#include "models/worker.h"

#include <vector>
 
#define AREA_SIZE 256
#define AREA_W AREA_SIZE
#define AREA_H AREA_SIZE
#define AREA_TOTAL AREA_W * AREA_H

class Tile {
public:
	Tile() : blocked(false) { }
	bool blocked;
private:

};

class Area {
public:
	Tile tiles[AREA_TOTAL];
private:
};


class World {
public:
	World() : buildings(std::vector<Building>()), area(Area()) { }
	Tile& getTile (Tile2 position);
	std::vector<Building> buildings;
private:
	Area area;
};


