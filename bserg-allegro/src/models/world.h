#pragma once

#include "engine.h"
#include "models/building.h"
#include <vector>
 
#define AREA_SIZE 256
#define AREA_W AREA_SIZE
#define AREA_H AREA_SIZE
#define AREA_TOTAL AREA_W * AREA_H

class Tile {
public:
	bool blocked;
private:

};

class Area {
public:
private:
	Tile tiles[AREA_TOTAL];
};


class World {
public:
	World() : buildings(std::vector<Building>(100)), area(Area()) { }
	Tile getTile(int2 position);
	

private:
	Area area;
	std::vector<Building> buildings;
};

