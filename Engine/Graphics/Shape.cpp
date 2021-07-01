#include "Shape.h"

namespace nc
{
	void Shape::Draw(Core::Graphics& graphics, nc::Vector2 position, float scale)
	{
		graphics.SetColor(color);

		for (size_t i = 0; i < points.size() - 1; i++)
		{
			nc::Vector2 p1 = position + (points[i] * scale);
			nc::Vector2 p2 = position + (points[i + 1] * scale);

			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
}