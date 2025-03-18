#include <LinearAlgebra/VectorBase.hpp>
#include <gtest/gtest.h>
#include <memory>

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
        VectorBase<int> vector(std::vector<int>{1, 2, 3, 4, 5});
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
        VectorBase<int> vector({1, 2, 3, 4, 5});
        EXPECT_EQ(vector.GetValue(0), 1);
        vector.SetValue(0, 3);
        EXPECT_EQ(vector.GetValue(0), 3);
    }

    TEST(VectorBaseTests, SetValue_WhenOutInRange_ShouldThrow)
    {
        VectorBase<int> vector({1, 2, 3, 4, 5});
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
        ColumnVector<int> vec({1, 2, 3});
        std::stringstream stream;
        stream << vec;
        EXPECT_EQ(stream.str(), "Vec3[1, 2, 3]");
    }

    TEST(ColumnVectorTests, SumInt_WhenDimensionsMatch_ShouldResultCorrectSum)
    {
        ColumnVector<int> lhs({1, 2, 3, 4, 5});
        ColumnVector<int> rhs({7, 8, 5, 9, 1});
        ColumnVector<int> result = lhs + rhs;
        ColumnVector<int> expectedResult({8, 10, 8, 13, 6});
        EXPECT_TRUE(result.ElementwiseEquals(expectedResult));
    }

    TEST(ColumnVectorTests, SumFloat_WhenDimensionsMatch_ShouldResultCorrectSum)
    {
        ColumnVector<float> lhs({1, 2, 3, 4, 5});
        ColumnVector<float> rhs({7, 8, 5, 9, 1});
        ColumnVector<float> result = lhs + rhs;
        ColumnVector<float> expectedResult({8, 10, 8, 13, 6});
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
        ColumnVector<int> lhs({1, 2, 3, 4, 5});
        ColumnVector<int> rhs({7, 8, 5, 9, 1});
        ColumnVector<int> result1 = lhs - rhs;
        ColumnVector<int> result2 = rhs - lhs;
        EXPECT_TRUE(result1.ElementwiseEquals(ColumnVector<int>({-6, -6, -2, -5, 4})));
        EXPECT_TRUE(result2.ElementwiseEquals(ColumnVector<int>({6, 6, 2, 5, -4})));
    }

    TEST(ColumnVectorTests, SubtractInt_WhenDimensionsMisMatch_ShouldThrow)
    {
        ColumnVector<int> lhs(5);
        ColumnVector<int> rhs(4);
        EXPECT_THROW(lhs - rhs, std::invalid_argument);
    }

    TEST(ColumnVectorTests, ScalarProduct_WhenVectorIsNotEmpty_ShouldReturnScalarProduct)
    {
        ColumnVector<float> lhs = {1, 2, 3, 4, 5, 6, 7, 8};
        ColumnVector<float> result1 = 5 * lhs;
        ColumnVector<float> result2 = lhs * 5;
        ColumnVector<float> expectedResult = {5, 10, 15, 20, 25, 30, 35, 40};
        EXPECT_TRUE(result1.ElementwiseCompare(expectedResult, 1e-5f));
        EXPECT_TRUE(result2.ElementwiseCompare(expectedResult, 1e-5f));
    }

    TEST(ColumnVectorTests, Constructor_WhenUsingInitializerList_ShouldHaveValues)
    {
        ColumnVector<float> value({1, 2, 3, 4});
        EXPECT_EQ(value.GetLength(), 4);
        EXPECT_EQ(value[0], 1);
        EXPECT_EQ(value[1], 2);
        EXPECT_EQ(value[2], 3);
        EXPECT_EQ(value[3], 4);
    }

    TEST(ColumnVectorTests, Constructor_WhenUsingEmptyInitializerList_ShouldBeEmpty)
    {
        ColumnVector<float> value({});
        EXPECT_EQ(value.GetLength(), 0);
    }

    TEST(ColumnVectorTests, Assignment_WhenUsingInitializerList_ShouldHaveValues)
    {
        ColumnVector<float> value = {1, 2, 3, 4};
        EXPECT_EQ(value.GetLength(), 4);
        EXPECT_EQ(value[0], 1);
        EXPECT_EQ(value[1], 2);
        EXPECT_EQ(value[2], 3);
        EXPECT_EQ(value[3], 4);
    }

    TEST(ColumnVectorTests, Assignment_WhenUsingEmptyInitializerList_ShouldBeEmpty)
    {
        ColumnVector<float> value = {};
        EXPECT_EQ(value.GetLength(), 0);
    }

    TEST(ColumnVectorTests, Fill_WhenVectorIsNotEmpty_ShouldHaveIdenticalValues)
    {
        ColumnVector<float> temp(20);
        temp.Fill(7.3f);
        EXPECT_EQ(temp.GetLength(), 20);
        for (size_t i = 0; i < 20; i++)
        {
            EXPECT_EQ(temp[i], 7.3f);
        }
    }

    TEST(RowVectorTests, SumInt_WhenDimensionsMatch_ShouldResultCorrectSum)
    {
        RowVector<int> lhs({1, 2, 3, 4, 5});
        RowVector<int> rhs({7, 8, 5, 9, 1});
        RowVector<int> result = lhs + rhs;
        RowVector<int> expectedResult({8, 10, 8, 13, 6});
        EXPECT_TRUE(result.ElementwiseEquals(expectedResult));
    }

    TEST(RowVectorTests, SumFloat_WhenDimensionsMatch_ShouldResultCorrectSum)
    {
        RowVector<float> lhs({1, 2, 3, 4, 5});
        RowVector<float> rhs({7, 8, 5, 9, 1});
        RowVector<float> result = lhs + rhs;
        RowVector<float> expectedResult({8, 10, 8, 13, 6});
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
        RowVector<int> lhs({1, 2, 3, 4, 5});
        RowVector<int> rhs({7, 8, 5, 9, 1});
        RowVector<int> result1 = lhs - rhs;
        RowVector<int> result2 = rhs - lhs;
        EXPECT_TRUE(result1.ElementwiseEquals(RowVector<int>({-6, -6, -2, -5, 4})));
        EXPECT_TRUE(result2.ElementwiseEquals(RowVector<int>({6, 6, 2, 5, -4})));
    }

    TEST(RowVectorTests, SubtractInt_WhenDimensionsMisMatch_ShouldThrow)
    {
        RowVector<int> lhs(5);
        RowVector<int> rhs(4);
        EXPECT_THROW(lhs - rhs, std::invalid_argument);
    }

    TEST(RowVectorTests, ScalarProduct_WhenVectorIsNotEmpty_ShouldReturnScalarProduct)
    {
        RowVector<float> lhs = {1, 2, 3, 4, 5, 6, 7, 8};
        RowVector<float> result1 = 5 * lhs;
        RowVector<float> result2 = lhs * 5;
        RowVector<float> expectedResult = {5, 10, 15, 20, 25, 30, 35, 40};
        EXPECT_TRUE(result1.ElementwiseCompare(expectedResult, 1e-5f));
        EXPECT_TRUE(result2.ElementwiseCompare(expectedResult, 1e-5f));
    }

    TEST(RowVectorTests, Transposed_WhenNonEmpty_ShouldReturnColumnVector)
    {
        RowVector<float> lhs = {1, 2, 3, 4, 5, 6, 7, 8};
        ColumnVector<float> transposed = lhs.Transposed();
        EXPECT_TRUE(transposed.Transposed().ElementwiseCompare(lhs, 1e-5f));
    }

    TEST(RowVectorTests, Constructor_WhenUsingInitializerList_ShouldHaveValues)
    {
        RowVector<float> value({1, 2, 3, 4});
        EXPECT_EQ(value.GetLength(), 4);
        EXPECT_EQ(value[0], 1);
        EXPECT_EQ(value[1], 2);
        EXPECT_EQ(value[2], 3);
        EXPECT_EQ(value[3], 4);
    }

    TEST(RowVectorTests, Constructor_WhenUsingEmptyInitializerList_ShouldBeEmpty)
    {
        RowVector<float> value({});
        EXPECT_EQ(value.GetLength(), 0);
    }

    TEST(RowVectorTests, Assignment_WhenUsingInitializerList_ShouldHaveValues)
    {
        RowVector<float> value = {1, 2, 3, 4};
        EXPECT_EQ(value.GetLength(), 4);
        EXPECT_EQ(value[0], 1);
        EXPECT_EQ(value[1], 2);
        EXPECT_EQ(value[2], 3);
        EXPECT_EQ(value[3], 4);
    }

    TEST(RowVectorTests, Assignment_WhenUsingEmptyInitializerList_ShouldBeEmpty)
    {
        RowVector<float> value = {};
        EXPECT_EQ(value.GetLength(), 0);
    }

    TEST(RowVectorTests, Fill_WhenVectorIsNotEmpty_ShouldHaveIdenticalValues)
    {
        RowVector<float> temp(20);
        temp.Fill(7.3f);
        EXPECT_EQ(temp.GetLength(), 20);
        for (size_t i = 0; i < 20; i++)
        {
            EXPECT_EQ(temp[i], 7.3f);
        }
    }

    TEST(RowVectorTests, ColumnVectorProduct_WhenSameLength1_ShouldReturnInnerProduct)
    {
        RowVector<int> row(20);
        ColumnVector<int> column(20);
        row.Fill(5);
        column.Fill(5);
        int innerProduct = row * column;
        EXPECT_EQ(innerProduct, 500);
    }

    TEST(RowVectorTests, ColumnVectorProduct_WhenSameLength2_ShouldReturnInnerProduct)
    {
        RowVector<int> row = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        ColumnVector<int> column = {5, 4, 3, 2, 0, 1, 5, 3, 2, 3};
        int innerProduct = row * column;
        EXPECT_EQ(innerProduct, 143);
    }

    TEST(RowVectorTests, ColumnVectorProduct_WhenNotSameLength_ShouldThrow)
    {
        RowVector<int> row(21);
        ColumnVector<int> column(20);
        row.Fill(5);
        column.Fill(5);
        EXPECT_THROW(row * column, std::invalid_argument);
    }

    TEST(VEctorBaseTest, Iterator_WhenLoopingThroughVector_ShouldGiveAllElement)
    {
        ColumnVector<int> vector = {1, 2, 3, 4, 5};
        size_t count = 0;
        for (VectorIterator<int> i = vector.begin(); i != vector.end(); ++i)
        {
            EXPECT_EQ(*i, vector[count++]);
        }
        EXPECT_EQ(count, 5);
    }
}