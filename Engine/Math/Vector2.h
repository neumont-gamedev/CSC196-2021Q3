#pragma once
#include <cmath>

namespace nc
{
	struct Vector2
	{
		float x, y;

		Vector2() : x{ 0 }, y{ 0 } {}
		Vector2(float x, float y) : x{ x }, y{ y } {}
		Vector2(int x, int y) : x{ static_cast<float>(x) }, y{ static_cast<float>(y) } {}

		float operator [] (size_t index) { return (&x)[index]; }

		Vector2 operator + (const Vector2& v) const { return { x + v.x, y + v.y }; }
		Vector2 operator * (float s) const { return { x * s, y * s }; }
		Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
		Vector2& operator *= (float s) { x *= s; y *= s; return *this; }

		float Length();
		float LengthSqr();
	};

	inline float Vector2::Length()
	{
		return std::sqrt(x * x + y * y);
	}

	inline float Vector2::LengthSqr()
	{
		return (x * x + y * y);
	}


}
