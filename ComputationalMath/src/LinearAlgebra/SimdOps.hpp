#pragma once
#include <stdlib.h>

namespace LinearAlgebra
{
    namespace SimdOps
    {
        int* Sum(const int* left, const int* right, size_t length);
        void Sum(const int* left, const int* right, size_t length, int* result);

        int* Subtract(const int* left, const int* right, size_t length);
    }
}
