#include "models\building.h"

#include "bserg/images.h"

#include "globals.h"

const BuildingSpecification* specs[BuildingType::COUNT];

const BuildingSpecification* getSpec(BuildingType type) { return specs[(int)type]; }

void loadSpecs() {
	specs[(int)BuildingType::Storage] = new BuildingSpecification(CL_ORANGE, Tile2(2, 3));
	specs[(int)BuildingType::Barracks] = new BuildingSpecification(bserg::images::tent, Tile2(6, 6));
	specs[(int)BuildingType::Maintainance] = new BuildingSpecification(CL_WINE, Tile2(3, 5));
	specs[(int)BuildingType::Command] = new BuildingSpecification(CL_RAISIN_BLACK, Tile2(2, 2));
	specs[(int)BuildingType::WorkerHousing] = new BuildingSpecification(CL_GREY, Tile2(6, 2));
}

Unit2 drawBuilding(ALLEGRO_BITMAP* bitmap, Tile2 size, Tile2 topLeftTile, ALLEGRO_COLOR color) {

	// Calculate stuff
	Unit2 pos(topLeftTile);
	Unit2 unitSize(size);

	int2 sourceSize = int2(al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap));

	// Draw building
    al_draw_tinted_scaled_bitmap(bitmap, color, 0, 0, sourceSize.x, sourceSize.y, pos.x, pos.y, unitSize.x, unitSize.y, 0);

	return pos;
}

Unit2 drawBuilding(const Building &building) {
	const BuildingSpecification* spec = getSpec(building.type);

	return drawBuilding(spec->bitmap, spec->size, building.topLeftTile);
}
