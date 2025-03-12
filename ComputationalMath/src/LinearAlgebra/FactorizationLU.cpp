#include "FactorizationLU.h"

size_t *LinearAlgebra::Factorization::IntRange(size_t max)
{
    size_t* val = new size_t[max];
    for (int i = 0; i < max; i++)
    {
        val[i] = i;
    }
    return val;
}
