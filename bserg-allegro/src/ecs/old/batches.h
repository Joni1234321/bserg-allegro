#pragma once

#include "engine.h"
#include "components.h"
#include <vector>

namespace ecs {
	template <typename T>
	using Components = std::vector<T>;

	struct UnitBatch {

		UnitBatch(uint32_t reserve) {
			positions.reserve(reserve);
			nextPositions.reserve(reserve);
			moveGoals.reserve(reserve);
			positionAnimations.reserve(reserve);
			attacks.reserve(reserve);
			enabledComponents.reserve(reserve);
		}

		Components<PositionComponent> positions;
		Components<PositionNextComponent> nextPositions;
		Components<MoveGoalComponent> moveGoals;
		Components<PositionAnimationComponent> positionAnimations;
		Components<AttackComponent> attacks;

		Components<UnitEnabledComponentsComponent> enabledComponents;
	};

	struct TreeBatch {
		TreeBatch(uint32_t reserve) {
			positions.reserve(reserve);
		}
		Components<StaticPositionComponent> positions;
	};
}