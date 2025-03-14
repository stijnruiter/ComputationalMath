#include <gtest/gtest.h>
#include <Geometry/Structures/Rectangle.h>

namespace Geometry 
{
	TEST(RectangleTests, Constructor_WhenUsingDefault_ShouldBeZeroValued) {
		Rectangle rectangle;
		ASSERT_NEAR(rectangle.Left, 0.0f, FLT_EPSILON);
		ASSERT_NEAR(rectangle.Right, 0.0f, FLT_EPSILON);
		ASSERT_NEAR(rectangle.Bottom, 0.0f, FLT_EPSILON);
		ASSERT_NEAR(rectangle.Top, 0.0f, FLT_EPSILON);
	}

	TEST(RectangleTests, Constructor_WhenAssigningValues_ShouldHaveCorrectFields) {
		Rectangle rectangle(5, 10, -10, 7);
		ASSERT_NEAR(rectangle.Left, 5.0f, FLT_EPSILON);
		ASSERT_NEAR(rectangle.Right, 10.0f, FLT_EPSILON);
		ASSERT_NEAR(rectangle.Bottom, -10.0f, FLT_EPSILON);
		ASSERT_NEAR(rectangle.Top, 7.0f, FLT_EPSILON);
	}

	TEST(RectangleTests, GetHeight_WhenTopIsHigherThanBottom_ShouldBePositive) {
		Rectangle rectangle(5, 10, -10, 7);
		ASSERT_NEAR(rectangle.GetHeight(), 17.0f, FLT_EPSILON);
	}

	TEST(RectangleTests, GetHeight_WhenTopIsLowerThanBottom_ShouldBePositive) {
		Rectangle rectangle(5, 10, 7, -10);
		ASSERT_NEAR(rectangle.GetHeight(), -17.0f, FLT_EPSILON);
	}

	TEST(RectangleTests, GetWidth_WhenTopIsHigherThanBottom_ShouldBePositive) {
		Rectangle rectangle(-10, 7, 5, 10);
		ASSERT_NEAR(rectangle.GetWidth(), 17.0f, FLT_EPSILON);
	}

	TEST(RectangleTests, GetWidth_WhenTopIsLowerThanBottom_ShouldBePositive) {
		Rectangle rectangle(7, -10, 5, 10);
		ASSERT_NEAR(rectangle.GetWidth(), -17.0f, FLT_EPSILON);
	}
}