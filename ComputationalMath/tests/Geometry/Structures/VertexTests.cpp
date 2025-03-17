#include <Geometry/Structures/Vertex.hpp>
#include <gtest/gtest.h>

namespace Geometry
{
    TEST(Vertex2FTests, Constructor_WhenUsingDefault_ShouldBeZeroValued)
    {
        Vertex2F vert;
        EXPECT_EQ(vert.X, 0);
        EXPECT_EQ(vert.Y, 0);
    }
    
    TEST(Vertex2FTests, Constructor_WhenUsingValues_ShouldHaveValues)
    {
        Vertex2F vert(3, 4);
        EXPECT_EQ(vert.X, 3);
        EXPECT_EQ(vert.Y, 4);
    }
    
    TEST(Vertex2FTests, Constructor_WhenUsingInitializerList_ShouldHaveListValues)
    {
        Vertex2F vert = {3, 4};
        EXPECT_EQ(vert.X, 3);
        EXPECT_EQ(vert.Y, 4);
    }
    
    TEST(Vertex2FTests, Constructor_WhenUsingWrongInitializerList_ShouldThrow)
    {
        EXPECT_THROW(Vertex2F({1, 2, 3}), std::invalid_argument);
    }

    
    TEST(Vertex3FTests, Constructor_WhenUsingDefault_ShouldBeZeroValued)
    {
        Vertex3F vert;
        EXPECT_EQ(vert.X, 0);
        EXPECT_EQ(vert.Y, 0);
        EXPECT_EQ(vert.Z, 0);
    }
    
    TEST(Vertex3FTests, Constructor_WhenUsingValues_ShouldHaveValues)
    {
        Vertex3F vert(3, 4, 5);
        EXPECT_EQ(vert.X, 3);
        EXPECT_EQ(vert.Y, 4);
        EXPECT_EQ(vert.Z, 5);
    }
    
    TEST(Vertex3FTests, Constructor_WhenUsingInitializerList_ShouldHaveListValues)
    {
        Vertex3F vert = {3, 4, 5};
        EXPECT_EQ(vert.X, 3);
        EXPECT_EQ(vert.Y, 4);
        EXPECT_EQ(vert.Z, 5);
    }
    
    TEST(Vertex3FTests, Constructor_WhenUsingWrongInitializerList_ShouldThrow)
    {
        EXPECT_THROW(Vertex3F({1, 2, 3, 5}), std::invalid_argument);
    }
}