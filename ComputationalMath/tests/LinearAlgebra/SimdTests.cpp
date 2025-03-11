#include <gtest/gtest.h>

#include <LinearAlgebra/SimdOps.h>

namespace LinearAlgebra
{
	TEST(SimdOpsTests, Sum) 
	{
		int n = 20;
		int* left = new int[n]
			{
				 1,  2,  3,  4,  5,
				 6,  7,  8,  9, 10,
				11, 12, 13, 14, 15, 
				16, 17, 18, 19, 20
			};
		int* right = new int[n]
			{
				 1,  2,  3,  4,  5,
				 6,  7,  8,  9, 10,
				11, 12, 13, 14, 15,
				16, 17, 18, 19, 20
			};
		int* expectedResult = new int[n]
			{
				 2,  4,  6,  8, 10,
				12, 14, 16, 18, 20,
				22, 24, 26, 28, 30,
				32, 34, 36, 38, 40
			};
		int* result = SimdOps::Sum(left, right, n);

		EXPECT_TRUE(std::equal(result, result + n, expectedResult));
	}

	TEST(SimdOpsTests, Subtract)
	{
		int n = 20;
		int* left = new int[n]
			{
				1, 2, 3, 4, 5,
				6, 7, 8, 9, 10,
				11, 12, 13, 14, 15,
				16, 17, 18, 19, 20
			};
		int* right = new int[n]
			{
				2, 4, 6, 8, 10,
				12, 14, 16, 18, 20,
				22, 24, 26, 28, 30,
				32, 34, 36, 38, 40
			};

		int* negLeft = new int[n]
			{
				-1, -2, -3, -4, -5,
				-6, -7, -8, -9, -10,
				-11, -12, -13, -14, -15,
				-16, -17, -18, -19, -20
			};
		int* result = SimdOps::Subtract(right, left, n);
		EXPECT_TRUE(std::equal(result, result + n, left));
		result = SimdOps::Subtract(left, right, n);
		EXPECT_TRUE(std::equal(result, result + n, negLeft));
	}
}