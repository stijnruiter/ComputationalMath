#pragma once

#include "Geometry/Structures/Vertex.h"
#include <vector>

namespace Geometry
{
	struct Rectangle
	{
	public:
		float Left;
		float Right;
		float Bottom;
		float Top;

		Rectangle();
		Rectangle(float left, float right, float bottom, float top);
		float GetWidth();
		float GetHeight();

		static Rectangle BoundingBox(const std::vector<Vertex2F>& vertices, float dilate);
	};
}