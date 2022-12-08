#pragma once
#include "math/mathb.h"

class Camera {
public:
	mathb::types::float2 position;
	
	void zoom(float d);

	inline mathb::types::int2 worldToScreen (mathb::types::float2 world) const { return mathb::types::int2((int)((world.x - position.x) * scale ), (int)((world.y - position.y) * scale)); }
	inline mathb::types::float2 screenToWorld(mathb::types::int2 screen) const { return mathb::types::float2(position.x + screen.x * invScale, position.y + screen.y * invScale); }

	void setScale(float scale);
	float getScale() const { return scale; }
	float getInvScale() const { return invScale; }

	float minScale = .2f, maxScale = 10.0f;
private:
	float scale = 1;
	float invScale = 1;
 
};