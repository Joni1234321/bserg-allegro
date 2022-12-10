#include "models/worker.h"

#include <vector>
#include <queue>

#include <allegro5/display.h>

#include "bserg/images.h"


namespace bserg {
	namespace worker {
		struct DrawComponent {
			float2 tilePosition;
		};

		struct TickComponent {
			Tile2 position;
		};

		struct MoveComponent {
			Tile2 target;
		};

		std::queue<size_t> idleWorkers;
		std::vector<MoveComponent> moveComponents;
		std::vector<DrawComponent> drawComponents;
		std::vector<TickComponent> tickComponents;

		void tick(World& world) {
			const float speed = 8;

			const size_t n = size();
			for (size_t i = 0; i < n; i++) {
				TickComponent& tickComponent = tickComponents[i];
				MoveComponent& moveComponent = moveComponents[i];

				Tile2 diff = moveComponent.target - tickComponent.position;
				if (diff.x)
					tickComponent.position.x += (diff.x > 0) * 2 - 1;
				else
					tickComponent.position.y += (diff.y > 0) * 2 - 1;

				// Check and reassign new job
				if (tickComponent.position == moveComponent.target)
					idleWorkers.emplace(i);
			}

			const size_t nIdle = idleWorkers.size();
			for (size_t i = 0; i < nIdle; i++) {
				size_t index = idleWorkers.front();
				idleWorkers.pop();
				moveComponents[index].target = Tile2(rand() % 64, rand() % 64);
			}
		}

		void drawAll() {
			ALLEGRO_BITMAP* bitmap = bserg::images::smiley;
			al_hold_bitmap_drawing(true);

			const size_t n = size();
			for (size_t i = 0; i < n; i++) {
				const TickComponent &tickComponent = tickComponents[i];
				
				draw(bitmap, tickComponent.position);
			}

			al_hold_bitmap_drawing(false);

		}

		void draw(ALLEGRO_BITMAP* bitmap, Tile2 tilePosition , ALLEGRO_COLOR color) {
			const Unit2 position(tilePosition);
			const int2 sourceSize = int2(al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap));
			al_draw_tinted_scaled_bitmap(bitmap, color, 0, 0, sourceSize.x, sourceSize.y, position.x, position.y, UNITS_PER_TILE, UNITS_PER_TILE, 0);

		}



		size_t add(Tile2 position) {
			Unit2 unitPosition = Unit2(position);
			moveComponents.emplace_back(position);
			drawComponents.emplace_back(float2(unitPosition.x, unitPosition.y));
			tickComponents.emplace_back(position);
			return size() + 1;
		}

		size_t size() {
			return moveComponents.size();
		}
	}
}