#pragma once
#include <vector>

#include "engine.h"
#include "overlay/overlay.h"

struct Objective {
	int2 position;
	bool contested;
};
class BattleOverlay : public Overlay {
public:
	BattleOverlay();
	void draw();
private:
	std::vector<Objective> objectives;

};

