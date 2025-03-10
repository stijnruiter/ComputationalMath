#include <gtest/gtest.h>

#include <LinearAlgebra/Matrix.h>

namespace LinearAlgebra
{
	TEST(MatrixTests, Constructor_WhenDefaultArgument_ShouldBeEmpty) {
		Matrix<int, 0, 0> matrix;
		EXPECT_EQ(matrix.GetRowCount(), 0);
		EXPECT_EQ(matrix.GetColumnCount(), 0);
		EXPECT_THROW(matrix.GetValue(0, 0), std::out_of_range);
	}

	TEST(MatrixTests, Constructor_WhenSizeIsGiven_ShouldCreateCorrectSize) {
		Matrix<int, 5, 3> matrix;
		EXPECT_EQ(matrix.GetRowCount(), 5);
		EXPECT_EQ(matrix.GetColumnCount(), 3);
		EXPECT_THROW(matrix.GetValue(5, 1), std::out_of_range);
		EXPECT_THROW(matrix.GetValue(4, 3), std::out_of_range);
	}

	TEST(MatrixTests, Constructor_WhenDataIsGiven_ShouldCreateMatrixWithCorrectValues) {
		Matrix<int, 3, 5> matrix(new int[15]
			{
				 1,  2,  3,  4,  5, 
				 6,  7,  8,  9, 10, 
				11, 12, 13, 14, 15, 
			});
		EXPECT_EQ(matrix.GetRowCount(), 3);
		EXPECT_EQ(matrix.GetColumnCount(), 5);

		EXPECT_EQ(matrix(0, 0), 1);
		EXPECT_EQ(matrix(0, 1), 2);
		EXPECT_EQ(matrix(0, 2), 3);
		EXPECT_EQ(matrix(0, 3), 4);
		EXPECT_EQ(matrix(0, 4), 5);

		EXPECT_EQ(matrix(1, 0), 6);
		EXPECT_EQ(matrix(1, 1), 7);
		EXPECT_EQ(matrix(1, 2), 8);
		EXPECT_EQ(matrix(1, 3), 9);
		EXPECT_EQ(matrix(1, 4), 10);

		EXPECT_EQ(matrix(2, 0), 11);
		EXPECT_EQ(matrix(2, 1), 12);
		EXPECT_EQ(matrix(2, 2), 13);
		EXPECT_EQ(matrix(2, 3), 14);
		EXPECT_EQ(matrix(2, 4), 15);
	}

	TEST(MatrixTests, Sum_WhenDataIsGiven_ShouldCreateMatrixWithCorrectValues) {
		Matrix<int, 3, 5> matrix(new int[15]
			{
				1, 2, 3, 4, 5,
				6, 7, 8, 9, 10,
				11, 12, 13, 14, 15,
			});

		Matrix<int, 3, 5> matrix2(new int[15]
			{
				1, 2, 3, 4, 5,
				6, 7, 8, 9, 10,
				11, 12, 13, 14, 15,
			});
		Matrix<int, 3, 5> result = matrix + matrix2;
		Matrix<int, 3, 5> expect(new int[15] 
			{
				 2,  4,  6,  8, 10,
				12, 14, 16, 18, 20,
				22, 24, 26, 28, 30,
			});

		EXPECT_EQ(result.ElementwiseEquals(expect), true);
	}

	TEST(MatrixTests, Subtract_WhenDataIsGiven_ShouldCreateMatrixWithCorrectValues) {
		Matrix<int, 4, 2> matrix(new int[8] {1, 2, 3, 4, 5, 6, 7, 8});
		Matrix<int, 4, 2> matrix2(new int[8] {7, 3, 5, 4, 10, 2, 12, 6});
		Matrix<int, 4, 2> result1 = matrix - matrix;
		Matrix<int, 4, 2> result2 = matrix - matrix2;
		Matrix<int, 4, 2> result3 = matrix2 - matrix;

		EXPECT_EQ(result1.ElementwiseEquals(Matrix<int, 4, 2>(new int[8] {0, 0, 0, 0, 0, 0, 0, 0})), true);
		EXPECT_EQ(result2.ElementwiseEquals(Matrix<int, 4, 2>(new int[8] {-6, -1, -2, 0, -5, 4, -5, 2})), true);
		EXPECT_EQ(result3.ElementwiseEquals(Matrix<int, 4, 2>(new int[8] {
			6, 1, 2, 0, 5, -4, 5, -2})), true);
	}

	TEST(MatrixTests, Product_WhenInteger_ShouldBeElementEquals) {
		Matrix<int, 3, 5> matrix(new int[15] {
				1, 2, 3, 4, 5,
				6, 7, 8, 9, 10,
				11, 12, 13, 14, 15});

		Matrix<int, 5, 2> matrix2(new int[15] {
				1, 2, 
				3, 4,
				5, 6,
				7, 8,
				9, 10});

		Matrix<int, 3, 2> result = matrix * matrix2;
		EXPECT_EQ(result.ElementwiseEquals(Matrix<int, 3, 2>(new int[6] {
			 95, 110, 
			220, 260, 
			345, 410 })), true);
	}


	TEST(MatrixTests, Product_WhenFloat_ShouldApproximatelyEquals) {
		Matrix<float, 3, 5> matrix(new float[15] {
			1, 2, 3, 4, 5,
			6, 7, 8, 9, 10,
			11, 12, 13, 14, 15});

		Matrix<float, 5, 2> matrix2(new float[15] {
			1, 2,
			3, 4,
			5, 6,
			7, 8,
			9, 10});

		Matrix<float, 3, 2> result = matrix * matrix2;
		EXPECT_EQ(result.ElementwiseCompare(Matrix<float, 3, 2>(new float[6] {
			95.0f, 110.0f,
				220, 260,
				345, 410 }), 1e-5f), true);
	}
}
