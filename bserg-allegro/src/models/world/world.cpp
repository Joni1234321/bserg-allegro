#include "models\world.h"

Tile& World::getTile(int2 pos) {
	return area.tiles[pos.y * AREA_W + pos.x];
}