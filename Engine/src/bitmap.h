#pragma once
#include <allegro5/color.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap.h>
#include "math/mathb.h"


namespace bitmap {
	ALLEGRO_BITMAP* createPixelRect(ALLEGRO_COLOR color, mathb::types::int2 size);
	ALLEGRO_BITMAP* createTileRect(ALLEGRO_COLOR color, mathb::types::int2 size);

	template<uint32_t N>
	ALLEGRO_BITMAP* square() {
		static ALLEGRO_BITMAP* sq = bitmap::createPixelRect(al_map_rgb(255, 255, 255), mathb::types::int2(N, N));
		return sq;
	}
}
