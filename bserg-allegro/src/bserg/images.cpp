#include "images.h"

#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/bitmap_io.h>
#include <allegro5/system.h>


#define GET_PATH(local) "img/" local

namespace bserg {
	namespace images {
		ALLEGRO_BITMAP* smiley, *tent;
	}
}

static ALLEGRO_BITMAP * loadBitmap(const char * localPath) {
	ALLEGRO_BITMAP * bitmap = al_load_bitmap(localPath);
	if (bitmap)
		return bitmap;

	printf("Failed Loading image at %s \n", localPath);
	assert(bitmap);
	return bitmap;
}

void bserg::images::load() {
	smiley = loadBitmap("img/smiley.png");
	tent = loadBitmap("img/tent.png");
	return;
}