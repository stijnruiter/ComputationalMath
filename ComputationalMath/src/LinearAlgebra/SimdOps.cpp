#include "SimdOps.h"
#include "SimdOps.h"
#include <immintrin.h>

namespace LinearAlgebra
{
    namespace SimdOps
    {
        int* Sum(const int* left, const int* right, size_t length)
        {
            int* result = new int[length];
            Sum(left, right, length, result);
            return result;
        }

        void Sum(const int* left, const int* right, size_t length, int* result)
        {
            __m256i* arr_1_ptr = (__m256i*)left;
            __m256i* arr_2_ptr = (__m256i*)right;
            __m256i* res_ptr = (__m256i*)result;

            size_t simdLoops = length / 8;
            size_t singleLoops = length - 8 * simdLoops;

            for (size_t simd = 0; simd < simdLoops; simd++)
            {
                __m256i reg_1_SSE = _mm256_load_si256(arr_1_ptr);
                __m256i reg_2_SSE = _mm256_load_si256(arr_2_ptr);
                __m256i sumRes = _mm256_add_epi32(reg_1_SSE, reg_2_SSE);
                //*(__m256i*) res_ptr = _mm256_add_epi32(reg_1_SSE, reg_2_SSE);
                _mm256_storeu_si256(res_ptr, sumRes);

                arr_1_ptr++;
                arr_2_ptr++;
                res_ptr++;
            }

            for (size_t a = 8 * simdLoops; a < length; a++)
            {
                result[a] = left[a] + right[a];
            }
        }

        int* Subtract(const int* left, const int* right, size_t length)
        {
            int* result = new int[length];
            __m256i* arr_1_ptr = (__m256i*)left;
            __m256i* arr_2_ptr = (__m256i*)right;
            __m256i* res_ptr = (__m256i*)result;

            size_t simdLoops = length / 8;
            size_t singleLoops = length - 8 * simdLoops;

            for (size_t simd = 0; simd < simdLoops; simd++)
            {
                __m256i reg_1_SSE = _mm256_load_si256(arr_1_ptr);
                __m256i reg_2_SSE = _mm256_load_si256(arr_2_ptr);
                *(__m256i*) res_ptr = _mm256_sub_epi32(reg_1_SSE, reg_2_SSE);
                //_mm256_storeu_si256(res_ptr, sumRes);

                arr_1_ptr++;
                arr_2_ptr++;
                res_ptr++;
            }

            for (size_t a = 8 * simdLoops; a < length; a++)
            {
                result[a] = left[a] - right[a];
            }

            return result;
        }
    }
}