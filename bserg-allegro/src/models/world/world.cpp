#include "models\world.h"

Tile& World::getTile(Tile2 position) {
	return area.tiles[position.y * AREA_W + position.x];
}