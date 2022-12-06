#pragma once
#include "allegro5/bitmap.h"

#include "extra/bitmap-creator.h"
#include "math/mathb.h"

namespace bitmap {
	template<uint32_t N>
	ALLEGRO_BITMAP* square() {
		static ALLEGRO_BITMAP* sq = bitmapCreatePixelRect(al_map_rgb(255, 255, 255), mathb::types::int2(N, N));
		return sq;
	}
}
