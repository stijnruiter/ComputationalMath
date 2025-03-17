#pragma once
#include <initializer_list>
#include <iostream>
#include <stdlib.h>

namespace Geometry
{
    struct LineElement
    {
        unsigned int I, J;
        LineElement();
        LineElement(unsigned int i, unsigned int j);
        LineElement(const std::initializer_list<unsigned int>& elements);
        friend std::ostream& operator<<(std::ostream& os, const LineElement& line);
    };

    struct TriangleElement
    {
        unsigned int I, J, K;
        TriangleElement();
        TriangleElement(unsigned int i, unsigned int j, unsigned int k);
        TriangleElement(const std::initializer_list<unsigned int>& elements);
        friend std::ostream& operator<<(std::ostream& os, const TriangleElement& Triangle);
    };
}