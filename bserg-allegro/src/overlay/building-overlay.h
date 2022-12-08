#pragma once

#include "overlay.h"
#include "models/world.h"

class BuildingOverlay : public Overlay {
public:
	void draw();
private:
};


bool tryPlaceBuilding(World& world, int2 topLeftTile, BuildingType type);
void buildingOverlaySelect( BuildingType);

