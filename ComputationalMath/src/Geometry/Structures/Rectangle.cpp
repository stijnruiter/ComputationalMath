#include "Rectangle.hpp"

#include <algorithm>
#include <limits>

namespace Geometry
{
    Rectangle::Rectangle() : Rectangle(0, 0, 0, 0)
    {
    }

    Rectangle::Rectangle(const float left, const float right, const float bottom, const float top)
    {
        Left = left;
        Right = right;
        Bottom = bottom;
        Top = top;
    }

    float Rectangle::GetWidth() const
    {
        return Right - Left;
    }

    float Rectangle::GetHeight() const
    {
        return Top - Bottom;
    }

#define MIN_FLOAT std::numeric_limits<float>::lowest()
#define MAX_FLOAT std::numeric_limits<float>::max()

    Rectangle Rectangle::BoundingBox(const std::vector<Vertex2F>& vertices, const float dilate)
    {
        Rectangle rect(MAX_FLOAT, MIN_FLOAT, MAX_FLOAT, MIN_FLOAT);

        for (const Vertex2F& vertex : vertices)
        {
            rect.Left = std::min(rect.Left, vertex.X - dilate);
            rect.Right = std::max(rect.Right, vertex.X + dilate);
            rect.Bottom = std::min(rect.Bottom, vertex.Y - dilate);
            rect.Top = std::max(rect.Top, vertex.Y + dilate);
        }
        return rect;
    }
}