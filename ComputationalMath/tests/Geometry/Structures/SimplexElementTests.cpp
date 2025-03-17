#include <Geometry/Structures/SimplexElements.hpp>
#include <gtest/gtest.h>

namespace Geometry
{
    TEST(LineElementTests, Constructor_WhenUsingDefault_ShouldBeZeroValued)
    {
        LineElement element;
        EXPECT_EQ(element.I, 0);
        EXPECT_EQ(element.J, 0);
    }
    
    TEST(LineElementTests, Constructor_WhenUsingValues_ShouldHaveValues)
    {
        LineElement element(3, 4);
        EXPECT_EQ(element.I, 3);
        EXPECT_EQ(element.J, 4);
    }
    
    TEST(LineElementTests, Constructor_WhenUsingInitializerList_ShouldHaveListValues)
    {
        LineElement element = {3, 4};
        EXPECT_EQ(element.I, 3);
        EXPECT_EQ(element.J, 4);
    }
    
    TEST(LineElementTests, Constructor_WhenUsingWrongInitializerList_ShouldThrow)
    {
        EXPECT_THROW(LineElement({1, 2, 3}), std::invalid_argument);
    }

    
    TEST(TriangleElementTests, Constructor_WhenUsingDefault_ShouldBeZeroValued)
    {
        TriangleElement element;
        EXPECT_EQ(element.I, 0);
        EXPECT_EQ(element.J, 0);
        EXPECT_EQ(element.K, 0);
    }
    
    TEST(TriangleElementTests, Constructor_WhenUsingValues_ShouldHaveValues)
    {
        TriangleElement element(3, 4, 5);
        EXPECT_EQ(element.I, 3);
        EXPECT_EQ(element.J, 4);
        EXPECT_EQ(element.K, 5);
    }
    
    TEST(TriangleElementTests, Constructor_WhenUsingInitializerList_ShouldHaveListValues)
    {
        TriangleElement element = {3, 4, 5};
        EXPECT_EQ(element.I, 3);
        EXPECT_EQ(element.J, 4);
        EXPECT_EQ(element.K, 5);
    }
    
    TEST(TriangleElementTests, Constructor_WhenUsingWrongInitializerList_ShouldThrow)
    {
        EXPECT_THROW(TriangleElement({1, 2, 3, 5}), std::invalid_argument);
    }
}