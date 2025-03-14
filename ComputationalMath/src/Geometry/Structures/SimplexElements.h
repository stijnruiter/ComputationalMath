#pragma once
#include <stdlib.h>
#include <iostream>

namespace Geometry
{
    struct LineElement
    {
        size_t I, J;
        LineElement();
        LineElement(size_t i, size_t j);
        friend std::ostream& operator<<(std::ostream& os, const LineElement& line);
    };

    struct TriangleElement
    {
        size_t I, J, K;
        TriangleElement();
        TriangleElement(size_t i, size_t j, size_t k);
        friend std::ostream& operator<<(std::ostream& os, const TriangleElement& Triangle);
    };
}