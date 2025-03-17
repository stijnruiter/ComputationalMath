#include <gtest/gtest.h>

#include <LinearAlgebra/SimdOps.hpp>

namespace LinearAlgebra
{
    TEST(SimdOpsTests, Sum)
    {
        int n = 21; // Not a multiple of 4
        int* left = new int[n]{
             1,  2,  3,  4,  5,
             6,  7,  8,  9, 10,
            11, 12, 13, 14, 15,
            16, 17, 18, 19, 20, 21};
        int* expectedResult = new int[n]{
             2,  4,  6,  8, 10,
            12, 14, 16, 18, 20,
            22, 24, 26, 28, 30,
            32, 34, 36, 38, 40, 42};
        int* result = SimdOps::Sum(left, left, n);

        EXPECT_TRUE(std::equal(result, result + n, expectedResult));
        EXPECT_EQ(left[0], 1);
    }

    TEST(SimdOpsTests, Subtract)
    {
        int n = 21; // Not a multiple of 4
        int* left = new int[n]{
             1,  2,  3,  4,  5,
             6,  7,  8,  9, 10,
            11, 12, 13, 14, 15,
            16, 17, 18, 19, 20, 21};
        int* right = new int[n]{
             2,  4,  6,  8, 10,
            12, 14, 16, 18, 20,
            22, 24, 26, 28, 30,
            32, 34, 36, 38, 40, 42};

        int* negLeft = new int[n]{
             -1,  -2,  -3,  -4,  -5,
             -6,  -7,  -8,  -9, -10,
            -11, -12, -13, -14, -15,
            -16, -17, -18, -19, -20, -21};
        int* result = SimdOps::Subtract(right, left, n);
        EXPECT_TRUE(std::equal(result, result + n, left));
        result = SimdOps::Subtract(left, right, n);
        EXPECT_TRUE(std::equal(result, result + n, negLeft));
    }

    TEST(SimdOpsTests, Subtract_NotAligned)
    {
        int n = 21;
        int* left = new int[n]{
             1,  2,  3,  4,  5,
             6,  7,  8,  9, 10,
            11, 12, 13, 14, 15,
            16, 17, 18, 19, 20, 21};
        int* right = new int[n]{
             2,  4,  6,  8, 10,
            12, 14, 16, 18, 20,
            22, 24, 26, 28, 30,
            32, 34, 36, 38, 40, 42};

        int* negLeft = new int[n]{
             -1,  -2,  -3,  -4,  -5,
             -6,  -7,  -8,  -9, -10,
            -11, -12, -13, -14, -15,
            -16, -17, -18, -19, -20, -21
		};
        int* result = SimdOps::Subtract(right, left, n);
        EXPECT_TRUE(std::equal(result, result + n, left));
        result = SimdOps::Subtract(left, right, n);
        EXPECT_TRUE(std::equal(result, result + n, negLeft));
    }
}