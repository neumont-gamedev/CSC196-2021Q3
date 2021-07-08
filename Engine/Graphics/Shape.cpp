#include "Shape.h"

namespace nc
{
	void Shape::Draw(Core::Graphics& graphics, Vector2 position, float angle, float scale)
	{
		graphics.SetColor(color);

		for (size_t i = 0; i < points.size() - 1; i++)
		{
			nc::Vector2 p1 = position + (Vector2::Rotate(points[i], angle) * scale);
			nc::Vector2 p2 = position + (Vector2::Rotate(points[i + 1], angle) * scale);

			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
}

