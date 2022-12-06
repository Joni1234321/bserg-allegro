#pragma once

namespace ecs {

	struct PositionComponent {
		float2 current;
	};
	struct PositionNextComponent {
		float2 next;
	};
	struct PositionAnimationComponent {
		float2 drawPosition;
	};
	struct MoveGoalComponent {
		float2 goal;
	};

	struct StaticPositionComponent {
		float2 position;
	};

	struct AttackComponent {
		uint32_t rounds;
		uint32_t range;
	};

	struct TargetComponent {

	};

	union UnitEnabledComponentsComponent {
		struct {
			bool positionAnimation : 1;
			bool moveGoal : 1;
			bool attack : 1;
			bool target : 1;
		};
		unsigned mask : 4 = 0b0011;
	};
}