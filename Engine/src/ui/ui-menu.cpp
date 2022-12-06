#include "ui/ui-menu.h"

#include "allegro5/allegro.h"
#include "example-bitmaps.h"
#include "inputs.h"
#include "collision.h"
#include "transforms.h"

namespace ui {
	// Create a horizontal menu attached to the top
	bool drawBottomMenu(const std::vector<Image> items, int offset, const ALLEGRO_COLOR background, int paddingX, int paddingY){
		al_use_transform(&TRANSFORM_UI);

		const size_t n = items.size();
		
		if (n == 0)
			return false; 

		const int w = items[0].w;
		const int h = items[0].h;

		const int menuW = w * n + offset * (n - 1) + paddingX * 2;
		const int menuH = h + paddingY * 2;
		const int distToEdgeX = (SCREEN_W - menuW) / 2;
		const int distToEdgeY = SCREEN_H - menuH;

		const int firstItemX = distToEdgeX + paddingX;

		al_draw_tinted_scaled_bitmap(bitmap::square<32>(), background, 0, 0, 32, 32, distToEdgeX, SCREEN_H - menuH, menuW, menuH, 0);

		bool hitUI = false;
		for (int i = 0; i < n; i++) {
			const int x = firstItemX + i * (w + offset);
			const int y = distToEdgeY + paddingY;

			Image image = items[i];

			// Collisions 
			if (!hitUI && collision::insideRect(MOUSE_X, MOUSE_Y, x, y, image.getX2(x), image.getY2(y))) {
				al_draw_tinted_bitmap(image.bitmap, al_map_rgba_f(.5f, .5f, .5f, 0.5f), x, y, 0);
				hitUI = true;
				continue;
			}

			// Draw bitmap
			al_draw_bitmap(image.bitmap, x, y, 0);
		}

		return hitUI;
	}
}