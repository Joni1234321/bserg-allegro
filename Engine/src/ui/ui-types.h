#pragma once

#include <allegro5/bitmap.h>

namespace ui {
	struct Image {
		ALLEGRO_BITMAP* bitmap;
		
		const uint32_t w, h;


		Image(ALLEGRO_BITMAP* bitmap, int w, int h) : bitmap(bitmap), w(w), h(h) { }

		inline int getX2(int x) const { return x + w; };
		inline int getY2(int y) const { return y + h; };
	};
}
