#include "unit.h"

#include "engine.h"
#include<cmath>

int2 Unit::halfSize(15, 10);

bool moveUnitTick(Unit& unit) {
	const float speed = 8, speedSqr = speed * speed;
	float2 d = unit.goal - unit.next;
	float distSqr = d.distSqr();

	if (distSqr < speedSqr) {
		unit.next = unit.goal;
		return true;
	}

	float dist = std::sqrt(distSqr);
	
	float k = speed / dist;
	unit.curr = unit.next;
	
	unit.next.x += d.x * k;
	unit.next.y += d.y * k;

	return false;
}

Unit::Unit(float2 spawn) : curr(spawn), next(spawn), goal(spawn)
{
}


