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

    std::ostream& operator<<(std::ostream& os, const TriangleElement& triangle)
    {
        return os << "(" << triangle.I << ", " << triangle.J << ", " << triangle.K << ")";
    };
}