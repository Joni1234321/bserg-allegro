#pragma once
#include "engine.h"


struct WorkerDrawData {
	float2 tilePosition;
};

struct WorkerTickData {
	Tile2 pos;
	Tile2 target;
};
