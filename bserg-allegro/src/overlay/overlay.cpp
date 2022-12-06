#include "overlay.h"


uint32_t _overlayID = 0;

void Overlay::draw() {
	
}

std::unordered_map<uint32_t, Overlay*> overlays;
Overlay* currentOverlay;

Overlay* getCurrentOverlay() {
	return currentOverlay;
}


