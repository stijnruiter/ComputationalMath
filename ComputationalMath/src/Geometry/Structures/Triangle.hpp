#pragma once

#include "Vertex.hpp"
#include <vector>

namespace Geometry
{
    struct Triangle
    {
        Vertex2F V1;
        Vertex2F V2;
        Vertex2F V3;

        Triangle() = default;
        Triangle(Vertex2F v1, Vertex2F v2, Vertex2F v3);

        bool ContainsVertex(Vertex2F vertex) const;
        static bool ContainsVertex(Vertex2F vertex, Vertex2F v1, Vertex2F v2, Vertex2F v3);

        Vertex3F GetAngles() const;

        float GetSmallestAngle() const;

        static float HalfPlaneSide(Vertex2F p1, Vertex2F p2, Vertex2F p3);

        static Triangle ContainingTriangle(const std::vector<Vertex2F>& vertices, float dilate);

        Vertex2F GetCircumcenter() const;
    };
}