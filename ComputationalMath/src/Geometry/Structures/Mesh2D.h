#pragma once

#include <vector>
#include "SimplexElements.h"
#include "Vertex.h"

namespace Geometry
{
    struct Mesh2D
    {
        std::vector<Vertex2F> Vertices;
        std::vector<TriangleElement> Interior;
        std::vector<LineElement> Boundary;

        Mesh2D() { }

        Mesh2D(size_t initialCapacityInterior, size_t initialCapacityBoundary);

        std::vector<LineElement> GetAllEdges() const;
    };
}