#include "Triangle.hpp"
#include "Rectangle.hpp"
#include <cmath>
#include <math.h>
#include <vector>

namespace Geometry
{
    Triangle::Triangle()
        : V1(), V2(), V3()
    {
    }

    Triangle::Triangle(Vertex2F v1, Vertex2F v2, Vertex2F v3)
        : V1(v1), V2(v2), V3(v3)
    {
    }

    bool Triangle::ContainsVertex(Vertex2F vertex) const
    {
        const float epsilon = 1e-8f;
        float d1 = Triangle::HalfPlaneSide(vertex, V1, V2);
        float d2 = Triangle::HalfPlaneSide(vertex, V2, V3);
        float d3 = Triangle::HalfPlaneSide(vertex, V3, V1);

        bool all_neg = (d1 <= epsilon) && (d2 <= epsilon) && (d3 <= epsilon);
        bool all_pos = (d1 >= -epsilon) && (d2 >= -epsilon) && (d3 >= -epsilon);

        return all_neg || all_pos;
    }

    bool Triangle::ContainsVertex(Vertex2F vertex, Vertex2F v1, Vertex2F v2, Vertex2F v3)
    {
        return Triangle(v1, v2, v3).ContainsVertex(vertex);
    }

    Vertex3F Triangle::GetAngles() const
    {
        Vertex3F result;
        Vertex2F dir1 = (V2 - V1).Normalized();
        Vertex2F dir2 = (V3 - V1).Normalized();
        result.X = std::acos(Vertex2F::DotProduct(dir1, dir2));
        Vertex2F dir3 = (V3 - V2).Normalized();
        result.Y = std::acos(Vertex2F::DotProduct(-1 * dir1, dir3));
        result.Z = M_PI - result.X - result.Y;
        return result;
    }

    float Triangle::HalfPlaneSide(Vertex2F p1, Vertex2F p2, Vertex2F p3)
    {
        return (p1.X - p3.X) * (p2.Y - p3.Y) - (p2.X - p3.X) * (p1.Y - p3.Y);
    }

    Triangle Triangle::ContainingTriangle(const std::vector<Vertex2F>& vertices, float dilate)
    {
        Rectangle boundingBox = Rectangle::BoundingBox(vertices, dilate);
        Vertex2F v1(boundingBox.Left, boundingBox.Bottom);
        Vertex2F v2(boundingBox.GetWidth() + boundingBox.GetHeight(), boundingBox.Bottom);
        Vertex2F v3(boundingBox.Left, boundingBox.GetWidth() + boundingBox.GetHeight());
        return Triangle(v1, v2, v3);
    }

    Vertex2F Triangle::GetCirclumcenter() const
    {
        float lengthSquared1 = (V1.X * V1.X + V1.Y * V1.Y);
        float lengthSquared2 = (V2.X * V2.X + V2.Y * V2.Y);
        float lengthSquared3 = (V3.X * V3.X + V3.Y * V3.Y);

        return Vertex2F(
            (lengthSquared1 * (V2.Y - V3.Y) + lengthSquared2 * (V3.Y - V1.Y) + lengthSquared3 * (V1.Y - V2.Y)) / (2 * (V1.X * (V2.Y - V3.Y) + V2.X * (V3.Y - V1.Y) + V3.X * (V1.Y - V2.Y))),
            (lengthSquared1 * (V2.X - V3.X) + lengthSquared2 * (V3.X - V1.X) + lengthSquared3 * (V1.X - V2.X)) / (2 * (V1.Y * (V2.X - V3.X) + V2.Y * (V3.X - V1.X) + V3.Y * (V1.X - V2.X))));
    }

    float Triangle::GetSmallestAngle() const
    {
        Vertex3F angles = GetAngles();
        return std::min(std::min(angles.X, angles.Y), angles.Z);
    }
}