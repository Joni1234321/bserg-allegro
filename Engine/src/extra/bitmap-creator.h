#pragma once

#include "allegro5/bitmap.h"
#include "math/mathb.h"

#define PIXELS_PER_TILE 64

ALLEGRO_BITMAP* bitmapCreateTileRect(ALLEGRO_COLOR color, mathb::types::int2 tileSize);
ALLEGRO_BITMAP* bitmapCreatePixelRect(ALLEGRO_COLOR color, mathb::types::int2 pixelSize);

