#include <gtest/gtest.h>

#include <LinearAlgebra/ColumnVector.h>

namespace LinearAlgebra
{
	TEST(ColumnVectorTests, Constructor_WhenDefaultArgument_ShouldBeEmpty) {
		ColumnVector<int> vector;
		EXPECT_EQ(vector.GetLength(), 0);
		EXPECT_THROW(vector.Get(0), std::out_of_range);
		EXPECT_THROW(vector.Set(0, 1), std::out_of_range);
	}

	TEST(ColumnVectorTests, Constructor_WhenSizeIsGiven_ShouldBeOfSize) {
		ColumnVector<int> vector(3);
		EXPECT_EQ(vector.GetLength(), 3);
		EXPECT_THROW(vector.Get(3), std::out_of_range);
		EXPECT_THROW(vector.Set(3, 1), std::out_of_range);
	}

	TEST(ColumnVectorTests, Constructor_WhenArrayAreGiven_ShouldHaveSameValuesAsArray) {
		int values[5] = { 1, 2, 3, 4, 5 };
		ColumnVector<int> vector(5, values);
		EXPECT_EQ(vector.GetLength(), 5);
		for (int i = 0; i < 5; i++)
		{
			EXPECT_EQ(vector.Get(i), i + 1);
		}
		EXPECT_THROW(vector.Get(5), std::out_of_range);
		EXPECT_THROW(vector.Set(5, 1), std::out_of_range);
	}

	TEST(ColumnVectorTests, Set_WhenIndexInRange_ShouldModifyIndex) {
		int values[5] = { 1, 2, 3, 4, 5 };
		ColumnVector<int> vector(5, values);
		for (int i = 0; i < 5; i++)
		{
			vector.Set(i, i + 6);
		}
		for (int i = 0; i < 5; i++)
		{
			EXPECT_EQ(vector.Get(i), i + 6);
		}
	}

	TEST(ColumnVectorTests, Set_WhenIndexOutInRange_ShouldThrow) {
		int values[5] = { 1, 2, 3, 4, 5 };
		ColumnVector<int> vector(5, values);
		EXPECT_THROW(vector.Set(5, 3), std::out_of_range);
	}
}
