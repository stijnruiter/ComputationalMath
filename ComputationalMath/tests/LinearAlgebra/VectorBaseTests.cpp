#include <LinearAlgebra/VectorBase.hpp>
#include <gtest/gtest.h>

namespace LinearAlgebra
{
    TEST(VectorBaseTests, Constructor_WhenDefault_ShouldBeEmpty)
    {
        VectorBase<int> vector;
        EXPECT_EQ(vector.GetLength(), 0);
        EXPECT_THROW(vector.GetValue(0), std::out_of_range);
    }

    TEST(VectorBaseTests, Constructor_WhenLengthIsGiven_ShouldBeCorrectLength)
    {
        VectorBase<int> vector(5);
        EXPECT_EQ(vector.GetLength(), 5);
        EXPECT_NO_THROW(vector.GetValue(0));
        EXPECT_NO_THROW(vector.GetValue(1));
        EXPECT_NO_THROW(vector.GetValue(2));
        EXPECT_NO_THROW(vector.GetValue(3));
        EXPECT_NO_THROW(vector.GetValue(4));
        EXPECT_THROW(vector.GetValue(5), std::out_of_range);
    }

    TEST(VectorBaseTests, Constructor_WhenDataIsGiven_ShouldHaveCorrectData)
    {
        VectorBase<int> vector(5, new int[5]{1, 2, 3, 4, 5});
        EXPECT_EQ(vector.GetLength(), 5);
        EXPECT_EQ(vector.GetValue(0), 1);
        EXPECT_EQ(vector.GetValue(1), 2);
        EXPECT_EQ(vector.GetValue(2), 3);
        EXPECT_EQ(vector.GetValue(3), 4);
        EXPECT_EQ(vector.GetValue(4), 5);
        EXPECT_THROW(vector.GetValue(5), std::out_of_range);
    }

    TEST(VectorBaseTests, SetValue_WhenInRange_ShouldSetValue)
    {
        VectorBase<int> vector(5, new int[5]{1, 2, 3, 4, 5});
        EXPECT_EQ(vector.GetValue(0), 1);
        vector.SetValue(0, 3);
        EXPECT_EQ(vector.GetValue(0), 3);
    }

    TEST(VectorBaseTests, SetValue_WhenOutInRange_ShouldThrow)
    {
        VectorBase<int> vector(5, new int[5]{1, 2, 3, 4, 5});
        EXPECT_THROW(vector.SetValue(5, 3), std::out_of_range);
    }

    TEST(VectorBaseTests, LeftShiftStream_WhenEmpty_ShouldReturnEmpty)
    {
        ColumnVector<int> vec;
        std::stringstream stream;
        stream << vec;
        EXPECT_EQ(stream.str(), "Vec0[]");
    }

    TEST(VectorBaseTests, LeftShiftStream_WhenNotEmpty_ShouldReturnVectorStream)
    {
        ColumnVector<int> vec(3, new int[3]{1, 2, 3});
        std::stringstream stream;
        stream << vec;
        EXPECT_EQ(stream.str(), "Vec3[1, 2, 3]");
    }

    TEST(ColumnVectorTests, SumInt_WhenDimensionsMatch_ShouldResultCorrectSum)
    {
        ColumnVector<int> lhs(5, new int[5]{1, 2, 3, 4, 5});
        ColumnVector<int> rhs(5, new int[5]{7, 8, 5, 9, 1});
        ColumnVector<int> result = lhs + rhs;
        ColumnVector<int> expectedResult(5, new int[5]{8, 10, 8, 13, 6});
        EXPECT_TRUE(result.ElementwiseEquals(expectedResult));
    }

    TEST(ColumnVectorTests, SumFloat_WhenDimensionsMatch_ShouldResultCorrectSum)
    {
        ColumnVector<float> lhs(5, new float[5]{1, 2, 3, 4, 5});
        ColumnVector<float> rhs(5, new float[5]{7, 8, 5, 9, 1});
        ColumnVector<float> result = lhs + rhs;
        ColumnVector<float> expectedResult(5, new float[5]{8, 10, 8, 13, 6});
        EXPECT_TRUE(result.ElementwiseCompare(expectedResult, 1e-5f));
    }

    TEST(ColumnVectorTests, SumInt_WhenDimensionsMisMatch_ShouldThrow)
    {
        ColumnVector<int> lhs(5);
        ColumnVector<int> rhs(4);
        EXPECT_THROW(lhs + rhs, std::invalid_argument);
    }

    TEST(ColumnVectorTests, SubtractInt_WhenDimensionsMatch_ShouldResultCorrectSubtraction)
    {
        ColumnVector<int> lhs(5, new int[5]{1, 2, 3, 4, 5});
        ColumnVector<int> rhs(5, new int[5]{7, 8, 5, 9, 1});
        ColumnVector<int> result1 = lhs - rhs;
        ColumnVector<int> result2 = rhs - lhs;
        EXPECT_TRUE(result1.ElementwiseEquals(ColumnVector<int>(5, new int[5]{-6, -6, -2, -5, 4})));
        EXPECT_TRUE(result2.ElementwiseEquals(ColumnVector<int>(5, new int[5]{6, 6, 2, 5, -4})));
    }

    TEST(ColumnVectorTests, SubtractInt_WhenDimensionsMisMatch_ShouldThrow)
    {
        ColumnVector<int> lhs(5);
        ColumnVector<int> rhs(4);
        EXPECT_THROW(lhs - rhs, std::invalid_argument);
    }

    TEST(RowVectorTests, SumInt_WhenDimensionsMatch_ShouldResultCorrectSum)
    {
        RowVector<int> lhs(5, new int[5]{1, 2, 3, 4, 5});
        RowVector<int> rhs(5, new int[5]{7, 8, 5, 9, 1});
        RowVector<int> result = lhs + rhs;
        RowVector<int> expectedResult(5, new int[5]{8, 10, 8, 13, 6});
        EXPECT_TRUE(result.ElementwiseEquals(expectedResult));
    }

    TEST(RowVectorTests, SumFloat_WhenDimensionsMatch_ShouldResultCorrectSum)
    {
        RowVector<float> lhs(5, new float[5]{1, 2, 3, 4, 5});
        RowVector<float> rhs(5, new float[5]{7, 8, 5, 9, 1});
        RowVector<float> result = lhs + rhs;
        RowVector<float> expectedResult(5, new float[5]{8, 10, 8, 13, 6});
        EXPECT_TRUE(result.ElementwiseCompare(expectedResult, 1e-5f));
    }

    TEST(RowVectorTests, SumInt_WhenDimensionsMisMatch_ShouldThrow)
    {
        RowVector<int> lhs(5);
        RowVector<int> rhs(4);
        EXPECT_THROW(lhs + rhs, std::invalid_argument);
    }

    TEST(RowVectorTests, SubtractInt_WhenDimensionsMatch_ShouldResultCorrectSubtraction)
    {
        RowVector<int> lhs(5, new int[5]{1, 2, 3, 4, 5});
        RowVector<int> rhs(5, new int[5]{7, 8, 5, 9, 1});
        RowVector<int> result1 = lhs - rhs;
        RowVector<int> result2 = rhs - lhs;
        EXPECT_TRUE(result1.ElementwiseEquals(RowVector<int>(5, new int[5]{-6, -6, -2, -5, 4})));
        EXPECT_TRUE(result2.ElementwiseEquals(RowVector<int>(5, new int[5]{6, 6, 2, 5, -4})));
    }

    TEST(RowVectorTests, SubtractInt_WhenDimensionsMisMatch_ShouldThrow)
    {
        RowVector<int> lhs(5);
        RowVector<int> rhs(4);
        EXPECT_THROW(lhs - rhs, std::invalid_argument);
    }
}