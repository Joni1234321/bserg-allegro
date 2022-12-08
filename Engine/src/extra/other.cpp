#include "globals.h"

using namespace mathb::types;

int2 TILE_TO_UNIT(const int2 tile) {
	return int2(tile.x << LOG_UNITS_PER_TILE, tile.y << LOG_UNITS_PER_TILE);
}
int2 UNIT_TO_TILE(const int2 unit) {
	return int2(unit.x >> LOG_UNITS_PER_TILE, unit.y >> LOG_UNITS_PER_TILE);
}
