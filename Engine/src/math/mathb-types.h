#pragma once
#include <cstdint>

#define UNITS_PER_TILE 64
#define LOG_UNITS_PER_TILE 6

// Ignore the first 6 bits, since 2^6 = 64
#define UNITS_PER_TILE_MASK 0xFFC0


namespace mathb {
	namespace types {
		
		struct float2 {
			float x, y;
			float2(float x, float y) : x(x), y(y) {}
			float2(float v) : x(v), y(v) {}
			float2() : x(0), y(0) {};
			
			float2 operator + (const float2& obj) const { return float2( x + obj.x, y + obj.y ); }
			float2 operator - (const float2& obj) const { return float2( x - obj.x, y - obj.y ); }
			float2 operator * (const float obj) const { return float2( x* obj, y* obj ); }

			float dist();
			float distSqr();

			void print();
		};

		struct int2 {
			int32_t x, y;
			int2(int32_t x, int32_t y) : x(x), y(y) {}
			int2(int32_t v) : x(v), y(v) {}
			int2() : x(0), y(0) {};

			int2 operator + (const int2& obj) const { return int2( x + obj.x, y + obj.y ); }
			int2 operator - (const int2& obj) const { return int2( x - obj.x, y - obj.y ); }
			int2 operator * (const int32_t obj) const { return int2( x * obj, y * obj ); }

			void print();
		};


		struct Unit2;
		struct Tile2;

		struct Unit2 {
			int32_t x, y;
			Unit2(int32_t x, int32_t y) : x(x), y(y) {}
			Unit2(int32_t v) : x(v), y(v) {}
			Unit2() : x(0), y(0) {};

			Unit2 operator + (const Unit2& obj) const { return Unit2(x + obj.x, y + obj.y); }
			Unit2 operator - (const Unit2& obj) const { return Unit2(x - obj.x, y - obj.y); }
			Unit2 operator * (const int32_t obj) const { return Unit2(x * obj, y * obj); }
			bool operator == (const Unit2& other) { return x == other.x && y == other.y; }

			
			explicit Unit2(const Tile2& tile);
		};
		
		struct Tile2 {
			int32_t x, y;
			Tile2(int32_t x, int32_t y) : x(x), y(y) {}
			Tile2(int32_t v) : x(v), y(v) {}
			Tile2() : x(0), y(0) {};


			Tile2 operator + (const Tile2& obj) const { return Tile2(x + obj.x, y + obj.y); }
			Tile2 operator - (const Tile2& obj) const { return Tile2(x - obj.x, y - obj.y); }
			Tile2 operator * (const int32_t obj) const { return Tile2(x * obj, y * obj); }
			bool operator == (const Tile2& other) { return x == other.x && y == other.y; }

			explicit Tile2(const Unit2& unit);
		};	

	}
}