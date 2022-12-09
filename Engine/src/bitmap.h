#pragma once
#include <allegro5/color.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap.h>
#include "math/mathb.h"


namespace bitmap {
	ALLEGRO_BITMAP* createRect(ALLEGRO_COLOR color, mathb::types::Unit2 size);

	template<uint32_t N>
	ALLEGRO_BITMAP* square() {
		static ALLEGRO_BITMAP* sq = bitmap::createRect(al_map_rgb(255, 255, 255), mathb::types::Unit2(N, N));
		return sq;
	}
}
