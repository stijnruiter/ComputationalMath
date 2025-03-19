#include "FactorizationLU.hpp"
#include <numeric>

size_t* LinearAlgebra::Factorization::IntRange(size_t max)
{
    size_t* val = new size_t[max];
    std::iota(val, val + max, 0);
    return val;
}
