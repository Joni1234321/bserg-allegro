#include "models\building.h"

const BuildingSpecification* specs[BuildingType::COUNT];

const BuildingSpecification* getSpec(BuildingType type) { return specs[(int)type]; }

void loadSpecs() {
	specs[(int)BuildingType::Storage] = new BuildingSpecification(CL_ORANGE, int2(2, 3));
	specs[(int)BuildingType::Barracks] = new BuildingSpecification(CL_BLUE, int2(6, 6));
}