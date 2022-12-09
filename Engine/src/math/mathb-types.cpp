#include "mathb.h"
#include "mathb-types.h"

#include <iostream>

namespace mathb {
	namespace types {

		void float2::print() {
			std::cout << x << " " << y << std::endl;
		}

		void int2::print() {
			std::cout << x << " " << y << std::endl;
		}

		float float2::dist() {
			return std::sqrt(x * x + y * y);
		}
		float float2::distSqr() {
			return x * x + y * y;
		}

		Unit2::Unit2(const Tile2& tile) : x(tile.x << LOG_UNITS_PER_TILE), y(tile.y << LOG_UNITS_PER_TILE) { }
		Tile2::Tile2(const Unit2& unit) : x(unit.x >> LOG_UNITS_PER_TILE), y(unit.y >> LOG_UNITS_PER_TILE) { }

	}
}