#include "camera.h"

#include <algorithm>

void Camera::zoom(float d) {
	scale = std::clamp(scale + d, minScale, maxScale);
	invScale = 1.0f / scale;
}



void Camera::setScale(float scale) {
	this->scale = scale; 
	invScale = 1.0f / scale; 
}