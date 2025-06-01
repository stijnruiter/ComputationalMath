#include "SimdOps.hpp"
#include <immintrin.h>

namespace LinearAlgebra::SimdOps
{
    int* Sum(const int* left, const int* right, size_t length)
    {
        int* result = new int[length];
        Sum(left, right, length, result);
        return result;
    }

    void Sum(const int* left, const int* right, size_t length, int* result)
    {
        __m128i* arr_1_ptr = (__m128i*)left;
        __m128i* arr_2_ptr = (__m128i*)right;
        __m128i* res_ptr = (__m128i*)result;

        size_t simdLoops = length / 4;
        size_t singleLoops = length - 4 * simdLoops;

        for (size_t simd = 0; simd < simdLoops; simd++)
        {

            __m128i reg_1_SSE = _mm_load_si128(arr_1_ptr);
            __m128i reg_2_SSE = _mm_load_si128(arr_2_ptr);
            __m128i sumRes = _mm_add_epi32(reg_1_SSE, reg_2_SSE);
            //*(__m256i*) res_ptr = _mm256_add_epi32(reg_1_SSE, reg_2_SSE);
            _mm_store_si128(res_ptr, sumRes);

            arr_1_ptr++;
            arr_2_ptr++;
            res_ptr++;
        }

        for (size_t a = 4 * simdLoops; a < length; a++)
        {
            result[a] = left[a] + right[a];
        }
    }

    int* Subtract(const int* left, const int* right, size_t length)
    {
        int* result = new int[length];
        __m128i* arr_1_ptr = (__m128i*)left;
        __m128i* arr_2_ptr = (__m128i*)right;
        __m128i* res_ptr = (__m128i*)result;

        size_t simdLoops = length / 4;
        size_t singleLoops = length - 4 * simdLoops;

        for (size_t simd = 0; simd < simdLoops; simd++)
        {
            __m128i reg_1_SSE = _mm_load_si128(arr_1_ptr);
            __m128i reg_2_SSE = _mm_load_si128(arr_2_ptr);
            *(__m128i*)res_ptr = _mm_sub_epi32(reg_1_SSE, reg_2_SSE);

            arr_1_ptr++;
            arr_2_ptr++;
            res_ptr++;
        }

        for (size_t a = 4 * simdLoops; a < length; a++)
        {
            result[a] = left[a] - right[a];
        }

        return result;
    }
}