#pragma once


namespace collision {
	inline bool insideRect(int x, int y, int x1, int y1, int x2, int y2) {
		if (x >= x1 && x <= x2 && y >= y1 && y <= y2)
			return true;
		return false;
	}
}