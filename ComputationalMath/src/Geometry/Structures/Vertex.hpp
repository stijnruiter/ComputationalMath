#pragma once

#include <initializer_list>

namespace Geometry
{
    struct Vertex3F;

    struct Vertex2F
    {
        float X;
        float Y;

        Vertex2F();
        Vertex2F(float x, float y);
        Vertex2F(const std::initializer_list<float>& value);

        Vertex2F operator+(Vertex2F rhs) const;
        Vertex2F operator-(Vertex2F rhs) const;
        Vertex2F operator*(float scalar) const;
        friend Vertex2F operator*(float scalar, Vertex2F rhs);

        float Length() const;
        float LengthSquared() const;

        void Normalize();
        Vertex2F Normalized() const;

        static float DotProduct(Vertex2F lhs, Vertex2F rhs);
        static float Distance(Vertex2F lhs, Vertex2F rhs);
        float DistanceTo(Vertex2F other) const;

        Vertex3F XY0() const;
    };

    struct Vertex3F
    {
        float X;
        float Y;
        float Z;

        Vertex3F();
        Vertex3F(float x, float y, float z);
        Vertex3F(Vertex2F vertex2, float z);
        Vertex3F(const std::initializer_list<float>& value);
    };
}