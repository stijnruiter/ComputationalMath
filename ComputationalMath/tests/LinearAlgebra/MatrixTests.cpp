#include <LinearAlgebra/Matrix.hpp>
#include <gtest/gtest.h>

namespace LinearAlgebra
{
    TEST(MatrixTests, Constructor_WhenColumnRowToLarge_ShouldThrow)
    {
        EXPECT_THROW(Matrix<int>(SIZE_MAX, 5), std::overflow_error);
    }

    TEST(MatrixTests, Constructor_WhenDefaultArgument_ShouldBeEmpty)
    {
        Matrix<int> matrix;
        EXPECT_EQ(matrix.GetRowCount(), 0);
        EXPECT_EQ(matrix.GetColumnCount(), 0);
        EXPECT_THROW(matrix.GetValue(0, 0), std::out_of_range);
    }

    TEST(MatrixTests, Constructor_WhenSizeIsGiven_ShouldCreateCorrectSize)
    {
        Matrix<int> matrix(5, 3);
        EXPECT_EQ(matrix.GetRowCount(), 5);
        EXPECT_EQ(matrix.GetColumnCount(), 3);
        EXPECT_THROW(matrix.GetValue(5, 1), std::out_of_range);
        EXPECT_THROW(matrix.GetValue(4, 3), std::out_of_range);
    }

    TEST(MatrixTests, Constructor_WhenDataIsGiven_ShouldCreateMatrixWithCorrectValues)
    {
        Matrix<int> matrix(3, 5, new int[15]{
            1,   2,  3,  4,  5,
            6,   7,  8,  9, 10,
            11, 12, 13, 14, 15
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

    TEST(MatrixTests, LeftShiftStream_WhenEmpty_ShouldReturnEmpty)
    {
        Matrix<int> mat;
        std::stringstream stream;
        stream << mat;
        EXPECT_EQ(stream.str(), "Mat0x0[]");
    }

    TEST(MatrixTests, LeftShiftStream_WhenColumnEmpty_ShouldReturnEmpty)
    {
        Matrix<int> mat(5, 0);
        std::stringstream stream;
        stream << mat;
        EXPECT_EQ(stream.str(), "Mat5x0[]");
    }
    TEST(MatrixTests, LeftShiftStream_WhenRowEmpty_ShouldReturnEmpty)
    {
        Matrix<int> mat(0, 5);
        std::stringstream stream;
        stream << mat;
        EXPECT_EQ(stream.str(), "Mat0x5[]");
    }

    TEST(MatrixTests, LeftShiftStream_WhenNotEmpty_ShouldReturnMatrixStream)
    {
        Matrix<int> vec(3, 2, new int[6]{
            1, 2, 
            3, 4, 
            5, 6
        });
        std::stringstream stream;
        stream << vec;
        EXPECT_EQ(stream.str(), "Mat3x2\n[[1, 2]\n[3, 4]\n[5, 6]]");
    }

    TEST(MatrixTests, GetValue_WhenIndexOutOfRange_ShouldThrow)
    {
        Matrix<int> matrix(3, 5);
        EXPECT_THROW(matrix(3, 4), std::out_of_range);
        EXPECT_THROW(matrix(2, 5), std::out_of_range);
    }

    TEST(MatrixTests, Sum_WhenDataIsInteger_ShouldCreateMatrixWithCorrectValues)
    {
        Matrix<int> matrix(3, 5, new int[15]{
             1,  2,  3,  4,  5,
             6,  7,  8,  9, 10,
            11, 12, 13, 14, 15,
        });

        Matrix<int> matrix2(3, 5, new int[15]{
             1,  2,  3,  4,  5,
             6,  7,  8,  9, 10,
            11, 12, 13, 14, 15,
        });
        Matrix<int> result = matrix + matrix2;
        Matrix<int> expect(3, 5, new int[15]{
            2,   4,  6,  8, 10,
            12, 14, 16, 18, 20,
            22, 24, 26, 28, 30,
        });

        EXPECT_EQ(result.ElementwiseEquals(expect), true);
    }

    TEST(MatrixTests, Sum_WhenDataIsFloat_ShouldCreateMatrixWithCorrectValues)
    {
        Matrix<float> matrix(3, 5, new float[15]{
             1,  2,  3,  4,  5,
             6,  7,  8,  9, 10,
            11, 12, 13, 14, 15
        });

        Matrix<float> matrix2(3, 5, new float[15]{
             1,  2,  3,  4,  5,
             6,  7,  8,  9, 10,
            11, 12, 13, 14, 15
        });
        Matrix<float> result = matrix + matrix2;
        Matrix<float> expect(3, 5, new float[15]{
             2,  4,  6,  8, 10,
            12, 14, 16, 18, 20,
            22, 24, 26, 28, 30
        });

        EXPECT_EQ(result.ElementwiseCompare(expect, 1e-5f), true);
    }

    TEST(MatrixTests, Sum_WhenDimensionMismatch_ShouldThrow)
    {
        Matrix<int> matrix4x2(4, 2);
        Matrix<int> matrix4x2_other(4, 2);
        Matrix<int> matrix4x3(4, 3);
        Matrix<int> matrix5x2(4, 3);

        EXPECT_NO_THROW(matrix4x2 + matrix4x2_other);
        EXPECT_THROW(matrix4x2 + matrix5x2, std::invalid_argument);
        EXPECT_THROW(matrix4x2 + matrix4x3, std::invalid_argument);
    }

    TEST(MatrixTests, Subtract_WhenDataIsGiven_ShouldCreateMatrixWithCorrectValues)
    {
        Matrix<int> matrix(4, 2, new int[8]{1, 2, 3, 4, 5, 6, 7, 8});
        Matrix<int> matrix2(4, 2, new int[8]{7, 3, 5, 4, 10, 2, 12, 6});
        Matrix<int> result1 = matrix - matrix;
        Matrix<int> result2 = matrix - matrix2;
        Matrix<int> result3 = matrix2 - matrix;

        EXPECT_EQ(result1.ElementwiseEquals(Matrix<int>(4, 2, new int[8]{0, 0, 0, 0, 0, 0, 0, 0})), true);
        EXPECT_EQ(result2.ElementwiseEquals(Matrix<int>(4, 2, new int[8]{-6, -1, -2, 0, -5, 4, -5, 2})), true);
        EXPECT_EQ(result3.ElementwiseEquals(Matrix<int>(4, 2, new int[8]{6, 1, 2, 0, 5, -4, 5, -2})), true);
    }

    TEST(MatrixTests, Subtract_WhenDimensionMismatch_ShouldThrow)
    {
        Matrix<int> matrix4x2(4, 2);
        Matrix<int> matrix4x2_other(4, 2);
        Matrix<int> matrix4x3(4, 3);
        Matrix<int> matrix5x2(4, 3);

        EXPECT_NO_THROW(matrix4x2 - matrix4x2_other);
        EXPECT_THROW(matrix4x2 - matrix4x3, std::invalid_argument);
        EXPECT_THROW(matrix4x2 - matrix5x2, std::invalid_argument);
    }

    TEST(MatrixTests, ProductMatrixMatrix_WhenInteger_ShouldBeElementEquals)
    {
        Matrix<int> matrix(3, 5, new int[15]{
            1,   2,  3,  4,  5,
            6,   7,  8,  9, 10,
            11, 12, 13, 14, 15
        });

        Matrix<int> matrix2(5, 2, new int[15]{
            1,  2, 
            3,  4, 
            5,  6, 
            7,  8, 
            9, 10
        });

        Matrix<int> result = matrix * matrix2;
        EXPECT_EQ(result.ElementwiseEquals(Matrix<int>(3, 2, new int[6]{
            95,  110, 
            220, 260, 
            345, 410
        })), true);
    }

    TEST(MatrixTests, ProductMatrixMatrix_WhenFloat_ShouldApproximatelyEquals)
    {
        Matrix<float> matrix(3, 5, new float[15]{
            1,   2,  3,  4,  5,
            6,   7,  8,  9, 10,
            11, 12, 13, 14, 15
        });

        Matrix<float> matrix2(5, 2, new float[15]{
            1, 2, 
            3, 4, 
            5, 6, 
            7, 8, 
            9, 10
        });

        Matrix<float> result = matrix * matrix2;
        EXPECT_EQ(result.ElementwiseCompare(Matrix<float>(3, 2, new float[6]{
             95.0f, 110.0f, 
            220   , 260, 
            345   , 410
        }), 1e-5f), true);
    }

    TEST(MatrixTests, ProductMatrixMatrix_WhenDimensionMismatch_ShouldThrow)
    {
        Matrix<float> matrix3x5(3, 5);
        Matrix<float> matrix2x3(2, 3);

        EXPECT_THROW(matrix3x5 * matrix2x3, std::invalid_argument);
        EXPECT_NO_THROW(matrix2x3 * matrix3x5);
    }

    TEST(MatrixTests, ProductMatrixScalar_WhenFloat_ShouldApproximatelyEquals)
    {
        Matrix<float> matrix(3, 5, new float[15]{
             1,  2,  3,  4,  5,
             6,  7,  8,  9, 10,
            11, 12, 13, 14, 15
        });

        Matrix<float> expectedResult(3, 5, new float[15]{
             5, 10, 15, 20, 25, 
            30, 35, 40, 45, 50, 
            55, 60, 65, 70, 75
        });
        Matrix<float> result1 = matrix * 5.0f;
        Matrix<float> result2 = 5.0f * matrix;

        EXPECT_EQ(result1.ElementwiseCompare(expectedResult, 1e-5f), true);
        EXPECT_EQ(result2.ElementwiseCompare(expectedResult, 1e-5f), true);
    }

    TEST(MatrixTests, ProductMatrixColumn_WhenFloat_ShouldApproximatelyEquals)
    {
        Matrix<float> matrix(3, 5, new float[15]{
            1,   2,  3,  4,  5,
            6,   7,  8,  9, 10,
            11, 12, 13, 14, 15,
        });
        ColumnVector<float> rhs(5, new float[5]{-5, 3, 2, 8, 4});
        ColumnVector<float> result = matrix * rhs;
        ColumnVector<float> expectedResult(3, new float[3]{59, 119, 179});

        EXPECT_EQ(result.ElementwiseCompare(expectedResult, 1e-5f), true);
    }

    TEST(MatrixTests, ProductMatrixColumn_WhenFloatDimensionMismatch_ShoulThrow)
    {
        Matrix<float> matrix(3, 5);
        ColumnVector<float> rhs1(5);
        ColumnVector<float> rhs2(4);
        EXPECT_NO_THROW(matrix * rhs1);
        EXPECT_THROW(matrix * rhs2, std::invalid_argument);
    }

    TEST(MatrixTests, ProductRowMatrix_WhenFloat_ShouldApproximatelyEquals)
    {
        Matrix<float> matrix(3, 5, new float[15]{
            1,   2,  3,  4,  5,
            6,   7,  8,  9, 10,
            11, 12, 13, 14, 15
        });
        RowVector<float> lhs(3, new float[3]{-2, 3, 2});
        RowVector<float> result = lhs * matrix;
        RowVector<float> expectedResult(5, new float[5]{38, 41, 44, 47, 50});
        EXPECT_EQ(result.ElementwiseCompare(expectedResult, 1e-5f), true);
    }

    TEST(MatrixTests, ProductRowMatrix_WhenFloatDimensionMismatch_ShouldThrow)
    {
        Matrix<float> matrix(3, 5);
        RowVector<float> lhs1(3);
        RowVector<float> lhs2(4);
        EXPECT_NO_THROW(lhs1 * matrix);
        EXPECT_THROW(lhs2 * matrix, std::invalid_argument);
    }

    TEST(MatrixTests, GetColumn_WhenIndexIsGiven_ShouldReturnColumnAtIndex)
    {
        int* entries = new int[15]{
            1, 2, 3, 4, 5,
            6, 7, 8, 9, 10,
            11, 12, 13, 14, 15};
        Matrix<int> storage(3, 5, entries);
        for (size_t i = 0; i < 5; i++)
        {
            ColumnVector<int> column = storage.GetColumn(i);
            EXPECT_EQ(column.GetLength(), 3);
            EXPECT_EQ(column[0], entries[i]);
            EXPECT_EQ(column[1], entries[i + 5]);
            EXPECT_EQ(column[2], entries[i + 10]);
        }
        EXPECT_THROW(storage.GetColumn(6), std::out_of_range);
        int* range = new int[16]{
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 1, 2, 3};
    }

    TEST(MatrixTests, GetRow_WhenIndexIsGiven_ShouldReturnRowAtIndex)
    {
        int* entries = new int[15]{
            1,   2,  3,  4,  5,
            6,   7,  8,  9, 10,
            11, 12, 13, 14, 15,
        };
        Matrix<int> storage(3, 5, entries);
        for (size_t i = 0; i < 3; i++)
        {
            RowVector<int> row = storage.GetRow(i);
            EXPECT_EQ(row.GetLength(), 5);
            EXPECT_EQ(row.GetValue(0), entries[i * 5 + 0]);
            EXPECT_EQ(row.GetValue(1), entries[i * 5 + 1]);
            EXPECT_EQ(row.GetValue(2), entries[i * 5 + 2]);
            EXPECT_EQ(row.GetValue(3), entries[i * 5 + 3]);
            EXPECT_EQ(row.GetValue(4), entries[i * 5 + 4]);
        }
        EXPECT_THROW(storage.GetRow(3), std::out_of_range);
    }
}
