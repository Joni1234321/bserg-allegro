#pragma once

#include "engine.h"
#include <vector>

class Unit {
public:
	Unit(float2);
	float2 curr, next, goal;
	static int2 halfSize;

	// Renderer
	float2 drawPosition;

	uint32_t rounds;
	uint32_t range;

	bool movePosition : 1;
	bool moveGoal : 1;
	bool attack : 1;
	bool target : 1;
};




bool moveUnitTick(Unit& unit);
