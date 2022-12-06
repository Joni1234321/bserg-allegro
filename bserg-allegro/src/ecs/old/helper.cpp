#include "helper.h"

#include "ecs.h"
#include "systems.h"

namespace ecs {
	// PSEUDO CODE TO HOW THIS WORKS
	void Start() {
		addBatch<UnitBatch>(new UnitBatch(10000));
	}

	void Update(float t, const Camera& camera) {
		UnitDrawSystem(getBatch<UnitBatch>(), t, camera);
	}

	void Tick() {
		UnitStateSystem(getBatch<UnitBatch>());
	}

	void SpawnUnit(UnitBatch& batch, float2 spawn) {
		batch.positions.emplace_back(spawn);
		batch.nextPositions.emplace_back(spawn);
		batch.moveGoals.emplace_back(spawn);
		batch.positionAnimations.emplace_back(spawn);
		batch.attacks.emplace_back(10, 100);

		batch.enabledComponents.emplace_back();
	}

	void DeleteUnits(UnitBatch& batch) {
		batch.positions.clear();
		batch.nextPositions.clear();
		batch.moveGoals.clear();
		batch.positionAnimations.clear();
		batch.attacks.clear();

		batch.enabledComponents.clear();
	}
}