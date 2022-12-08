#include "bitmap.h"

#include <allegro5/bitmap_lock.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/display.h>

#include "globals.h"

namespace bitmap {
	ALLEGRO_BITMAP* createPixelRect(ALLEGRO_COLOR color, mathb::types::int2 size) {
		ALLEGRO_BITMAP* bitmap = al_create_bitmap(size.x, size.y);
		al_lock_bitmap(bitmap, ALLEGRO_LOCK_WRITEONLY, 0);
		al_set_target_bitmap(bitmap);
		for (int y = 0; y < size.y; y++)
			for (int x = 0; x < size.x; x++)
				al_put_pixel(x, y, color);

		al_unlock_bitmap(bitmap);

		return bitmap;
	}

	ALLEGRO_BITMAP* createTileRect(ALLEGRO_COLOR color, mathb::types::int2 tileSize) {
		return createPixelRect(color, mathb::types::int2(tileSize.x * UNITS_PER_TILE, tileSize.y * UNITS_PER_TILE));
	}
}


