#include "models\building.h"

const BuildingSpecification* specs[BuildingType::COUNT];

const BuildingSpecification* getSpec(BuildingType type) { return specs[(int)type]; }

void loadSpecs() {
	specs[(int)BuildingType::Storage] = new BuildingSpecification(CL_ORANGE, int2(2, 3));
	specs[(int)BuildingType::Barracks] = new BuildingSpecification(CL_GRASS_1, int2(6, 6));
	specs[(int)BuildingType::Maintainance] = new BuildingSpecification(CL_WINE, int2(3, 5));
	specs[(int)BuildingType::Command] = new BuildingSpecification(CL_RAISIN_BLACK, int2(2, 2));
	specs[(int)BuildingType::WorkerHousing] = new BuildingSpecification(CL_GREY, int2(6, 2));
}