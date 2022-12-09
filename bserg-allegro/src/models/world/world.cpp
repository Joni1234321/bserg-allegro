#include "models\world.h"

Tile& World::getTile(Tile2 pos) {
	return area.tiles[pos.y * AREA_W + pos.x];
}