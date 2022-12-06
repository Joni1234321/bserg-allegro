#pragma once

#include "overlay.h"
#include "models/world.h"

class BuildingOverlay : public Overlay {
public:
	void draw();
private:
};


void buildingOverlaySelect(BuildingType);

