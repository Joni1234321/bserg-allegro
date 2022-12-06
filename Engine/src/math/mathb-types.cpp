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

	}
}