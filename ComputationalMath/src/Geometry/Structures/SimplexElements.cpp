#include "SimplexElements.hpp"

namespace Geometry
{
    LineElement::LineElement()
        : I(0), J(0)
    {
    }

    LineElement::LineElement(unsigned int i, unsigned int j)
        : I(i), J(j)
    {
    }

    LineElement::LineElement(const std::initializer_list<unsigned int>& elements)
    {
        if (elements.size() != 2)
            throw std::invalid_argument("Elements should only contain 2 elements");

        I = *elements.begin();
        J = *(elements.begin() + 1);
    }

    std::ostream& operator<<(std::ostream& os, const LineElement& line)
    {
        return os << "(" << line.I << ", " << line.J << ")";
    }

    TriangleElement::TriangleElement()
        : I(0), J(0), K(0)
    {
    }

    TriangleElement::TriangleElement(unsigned int i, unsigned int j, unsigned int k)
        : I(i), J(j), K(k)
    {
    }

    TriangleElement::TriangleElement(const std::initializer_list<unsigned int>& elements)
    {
        if (elements.size() != 3)
            throw std::invalid_argument("Elements should only contain 3 elements");

        I = *elements.begin();
        J = *(elements.begin() + 1);
        K = *(elements.begin() + 2);
    }

    std::ostream& operator<<(std::ostream& os, const TriangleElement& triangle)
    {
        return os << "(" << triangle.I << ", " << triangle.J << ", " << triangle.K << ")";
    };
}