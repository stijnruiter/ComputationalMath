#pragma once
#include "Geometry/Structures/Mesh2D.hpp"
#include "Geometry/Structures/Rectangle.hpp"

namespace Geometry
{
    Mesh2D CreateCircularMesh(float cx, float cy, float radius, float maxh);
    Mesh2D CreateRectangularMesh(const Rectangle& rect, unsigned int nx, unsigned int ny);
}