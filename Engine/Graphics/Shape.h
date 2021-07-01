#pragma once
#include "Math/Color.h"
#include "Math/Vector2.h"
#include <vector>

namespace nc
{
	class Shape
	{
	public:
		Shape() {}
		Shape(const std::vector<nc::Vector2>& points, const Color& color) : points{ points }, color{ color } {}

		void Draw(Core::Graphics& graphics, nc::Vector2 position, float scale = 1);

		void SetColor(const Color& color) { this->color = color; }
		const Color& GetColor() const { return color; }

	private:
		std::vector<Vector2> points;
		Color color;
	};
}
