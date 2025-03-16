#pragma once
#include <stdlib.h>
#include <iostream>

namespace Geometry
{
    struct LineElement
    {
        unsigned int I, J;
        LineElement();
        LineElement(unsigned int i, unsigned int j);
        friend std::ostream& operator<<(std::ostream& os, const LineElement& line);
    };

    struct TriangleElement
    {
        unsigned int I, J, K;
        TriangleElement();
        TriangleElement(unsigned int i, unsigned int j, unsigned int k);
        friend std::ostream& operator<<(std::ostream& os, const TriangleElement& Triangle);
    };
}