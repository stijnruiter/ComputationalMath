#include <cmath>
#include "Vertex.h"

namespace Geometry
{
    Vertex2F::Vertex2F() : X(0), Y(0) { }
    Vertex2F::Vertex2F(float x, float y) : X(x), Y(y) { }

    Vertex2F Vertex2F::operator+(Vertex2F rhs) const
    {
        rhs.X += X;
        rhs.Y += Y;
        return rhs;
    }

    Vertex2F Vertex2F::operator-(Vertex2F rhs) const
    {
        return Vertex2F(X - rhs.X, Y - rhs.Y);
    }

    Vertex2F Vertex2F::operator*(float scalar) const
    {
        return Vertex2F(scalar * X, scalar * Y);
    }

    Vertex2F operator*(float scalar, Vertex2F rhs)
    {
        rhs.X *= scalar;
        rhs.Y *= scalar;
        return rhs;
    }

    float Vertex2F::Length() const
    {
        return std::sqrt(LengthSquared());
    }

    float Vertex2F::LengthSquared() const
    {
        return X * X + Y * Y;
    }

    void Vertex2F::Normalize()
    {
        float length = Length();
        X /= length;
        Y /= length;
    }

    Vertex2F Vertex2F::Normalized() const
    {
        float length = Length();
        return Vertex2F(X / length, Y / length);
    }

    float Vertex2F::DotProduct(Vertex2F lhs, Vertex2F rhs)
    {
        return lhs.X * rhs.X + lhs.Y * rhs.Y;
    }

    float Vertex2F::Distance(Vertex2F lhs, Vertex2F rhs)
    {
        return (lhs - rhs).Length();
    }

    float Vertex2F::DistanceTo(Vertex2F other) const
    {
        return Vertex2F(X - other.X, Y - other.Y).Length();
    }

    Vertex3F Vertex2F::XY0() const
    {
        return Vertex3F(X, Y, 0.0f);
    }

    Vertex3F::Vertex3F() 
        : X(0), Y(0), Z(0)
    {
    }

    Vertex3F::Vertex3F(float x, float y, float z)
        : X(x), Y(y), Z(z)
    {
    }

    Vertex3F::Vertex3F(Vertex2F vertex2, float z)
        : X(vertex2.X), Y(vertex2.Y), Z(z)
    {
    }
}