#pragma once

#include "camera.h"

#include "ecs.h"
#include "batches.h"

namespace ecs {
	
	void Start();
	void Update(float t, const Camera& camera);
	void Tick();

	void SpawnUnit(UnitBatch& batch, float2 spawn);
	void DeleteUnits(UnitBatch& batch);


}