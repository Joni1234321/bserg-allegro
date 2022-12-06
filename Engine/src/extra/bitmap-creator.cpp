#include "bitmap-creator.h"

#include "allegro5/allegro5.h"


ALLEGRO_BITMAP* bitmapCreatePixelRect(ALLEGRO_COLOR color, mathb::types::int2 size) {
	ALLEGRO_BITMAP* bitmap = al_create_bitmap(size.x, size.y);
	al_set_target_bitmap(bitmap);
	for (int y = 0; y < size.y; y++)
		for (int x = 0; x < size.x; x++)
			al_put_pixel(x, y, color);

	al_unlock_bitmap(bitmap);

	return bitmap;
}

ALLEGRO_BITMAP* bitmapCreateTileRect(ALLEGRO_COLOR color, mathb::types::int2 tileSize)  {
	return bitmapCreatePixelRect(color, mathb::types::int2(tileSize.x * PIXELS_PER_TILE, tileSize.y * PIXELS_PER_TILE));
}