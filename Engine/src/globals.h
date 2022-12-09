#pragma once
#include "math/mathb-types.h"


#define ROTATION_TO_ANGLE(rotation) (rotation * ALLEGRO_PI / 2)
#define ROTATED_SIZE(rotation, size) (rotation & 1 ? Tile2(size.y, size.x) : size)