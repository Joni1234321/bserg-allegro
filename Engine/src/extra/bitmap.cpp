#include "bitmap.h"

#include <allegro5/bitmap_lock.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/display.h>

#include "globals.h"

namespace bitmap {
	ALLEGRO_BITMAP* createRect(ALLEGRO_COLOR color, mathb::types::Unit2 size) {
		ALLEGRO_BITMAP* bitmap = al_create_bitmap(size.x, size.y);
		al_lock_bitmap(bitmap, ALLEGRO_LOCK_WRITEONLY, 0);
		al_set_target_bitmap(bitmap);
		for (uint32_t y = 0; y < size.y; y++)
			for (uint32_t x = 0; x < size.x; x++)
				al_put_pixel(x, y, color);

		al_unlock_bitmap(bitmap);

		return bitmap;
	}
}


