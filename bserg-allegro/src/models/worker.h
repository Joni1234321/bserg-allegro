#pragma once
#include "engine.h"

#include "models/world.h"

namespace bserg {
	namespace worker {
		size_t add(Tile2 position);
		
		void drawAll();
		void draw(ALLEGRO_BITMAP* bitmap, Tile2 position, ALLEGRO_COLOR color = al_map_rgb_f(1, 1, 1));
		
		void tick(World&);

		size_t size();
	}
}