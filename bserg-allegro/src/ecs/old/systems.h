#pragma once

#include "camera.h"
#include "batches.h"

void UnitDrawSystem(ecs::UnitBatch& batch, float t, const Camera& camera);
void UnitStateSystem(ecs::UnitBatch& batch);