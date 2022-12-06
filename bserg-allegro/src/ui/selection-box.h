#pragma once

#include "engine.h"
#include "inputs.h"
#include "camera.h"

class SelectionBox {
public:
	SelectionBox(const Camera& camera) : camera(camera) { }
	void draw();
	void start(const MouseData&);
	void stop() { active = false; }

	bool intersectsRect(float x1, float y1, float x2, float y2) const;

private:
	const Camera& camera;

	bool active = false;

	// Store positions in world coordinates
	float2 startWorld;		
	float2 currWorld;

	// Except for u, u can stay
	int2 startScreen;

	// Corners of the selectionbox
	float2 topLeft, bottomRight;
};