#pragma once
#include "allegro5/bitmap.h"

struct UIImage {
	UIImage(ALLEGRO_BITMAP* bitmap, int x, int y, int w, int h) : bitmap(bitmap), 
		x(x), y(y), w(w), h(h),
		x2(x + w), y2(y + w)
	{
			
	}
	ALLEGRO_BITMAP* bitmap;
	int x, y, w, h;
	int x2, y2;
};