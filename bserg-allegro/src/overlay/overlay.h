#pragma once

#include <unordered_map>

class Overlay
{
public:
	virtual void draw();
};

Overlay* getCurrentOverlay();	


// Iterator
extern uint32_t _overlayID;
extern std::unordered_map<uint32_t, Overlay*> overlays;
extern Overlay* currentOverlay;

template <typename T>
inline uint32_t getOverlayID() {
	static const uint32_t id = _overlayID++;
	return id;
}

template <typename T>
void addOverlay(T* overlay) {
	overlays[getOverlayID<T>()] = overlay;
}

template <typename T>
void setOverlay() {
	currentOverlay = overlays[getOverlayID<T>()];
}

