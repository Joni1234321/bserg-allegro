#pragma once


namespace mathb {
	namespace types {
		
		class float2 {
		public:
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

		class int2 {
		public:
			int x, y;
			int2(int x, int y) : x(x), y(y) {}
			int2(int v) : x(v), y(v) {}
			int2() : x(0), y(0) {};

			int2 operator + (const int2& obj) const { return int2( x + obj.x, y + obj.y ); }
			int2 operator - (const int2& obj) const { return int2( x - obj.x, y - obj.y ); }
			int2 operator * (const int obj) const { return int2( x * obj, y * obj ); }

			void print();
		};

	}
}