#include "Vertex.hpp"
#include <cassert>
#include <cmath>
#include <stdexcept>

namespace Geometry
{
    Vertex2F::Vertex2F() : X(0), Y(0) {}
    Vertex2F::Vertex2F(const float x, const float y) : X(x), Y(y) {}

    Vertex2F::Vertex2F(const std::initializer_list<float>& value)
    {
        if (value.size() != 2)
            throw std::invalid_argument("Initializer list should only contain 2 values");

        X = *value.begin();
        Y = *(value.begin() + 1);
    }

    Vertex2F Vertex2F::operator+(Vertex2F rhs) const
    {
        rhs.X += X;
        rhs.Y += Y;
        return rhs;
    }

    Vertex2F Vertex2F::operator-(const Vertex2F rhs) const
    {
        return Vertex2F(X - rhs.X, Y - rhs.Y);
    }

    Vertex2F Vertex2F::operator*(const float scalar) const
    {
        return Vertex2F(scalar * X, scalar * Y);
    }

    Vertex2F operator*(const float scalar, Vertex2F rhs)
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
        const float length = Length();
        X /= length;
        Y /= length;
    }

    Vertex2F Vertex2F::Normalized() const
    {
        const float length = Length();
        return Vertex2F(X / length, Y / length);
    }

    float Vertex2F::DotProduct(const Vertex2F lhs, const Vertex2F rhs)
    {
        return lhs.X * rhs.X + lhs.Y * rhs.Y;
    }

    float Vertex2F::Distance(const Vertex2F lhs, const Vertex2F rhs)
    {
        return (lhs - rhs).Length();
    }

    float Vertex2F::DistanceTo(const Vertex2F other) const
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

    Vertex3F::Vertex3F(const float x, const float y, const float z)
        : X(x), Y(y), Z(z)
    {
    }

    Vertex3F::Vertex3F(const Vertex2F vertex2, const float z)
        : X(vertex2.X), Y(vertex2.Y), Z(z)
    {
    }

    Vertex3F::Vertex3F(const std::initializer_list<float>& value)
    {
        if (value.size() != 3)
            throw std::invalid_argument("Initializer list should only contain 3 values");
        X = *value.begin();
        Y = *(value.begin() + 1);
        Z = *(value.begin() + 2);
    }
}