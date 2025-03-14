#include <gtest/gtest.h>
#include <Geometry/RefinedDelaunay.h>

#include "TestHelper.h"

namespace Geometry 
{
    TEST(RefinedDelaunayTests, CreateTriangulation_WhenGraphHasLessThen3Vertices_ShouldThrowException)
    {
        PlanarStraightLineGraph graph;
        EXPECT_THROW(RefinedDelaunay::CreateTriangulation(graph), std::invalid_argument);
        graph.AddLineSegment(Vertex2F(0,0), Vertex2F(2, 2));
        EXPECT_THROW(RefinedDelaunay::CreateTriangulation(graph), std::invalid_argument);
    }   

    TEST(RefinedDelaunayTests, CreateTriangulation_WhenGraph1Polygon_CreatesDelaunayOfVertices)
    {
        std::vector<Vertex2F> zPolygon({ Vertex2F(0, 0), Vertex2F(1, 0), Vertex2F(0, 1), Vertex2F(1, 2) });
        PlanarStraightLineGraph graph;
        graph.AddLineSegments(zPolygon);
        Mesh2D mesh = RefinedDelaunay::CreateTriangulation(graph).ToMesh();

        EXPECT_EQUIVALENT_USING(mesh.Vertices, zPolygon, TestHelper::Vertex2FNearlyEqual);
        EXPECT_EQUIVALENT_USING(mesh.Interior, std::vector<TriangleElement>({
            TriangleElement(0, 1, 2),
            TriangleElement(1, 3, 2),
        }), TestHelper::TriangleElementCyclicalEqual);
    }

    TEST(RefinedDelaunayTests, Refine_WhenAngleIsLarge_ShouldResultSimpleDelaunay)
    {
        std::vector<Vertex2F> zPolygon({ Vertex2F(0, 0), Vertex2F(1, 0), Vertex2F(0, 1), Vertex2F(1, 2) });
        PlanarStraightLineGraph graph;
        graph.AddLineSegments(zPolygon);
        RefinedDelaunay delaunay = RefinedDelaunay::CreateTriangulation(graph);
        delaunay.Refine(25);
        Mesh2D mesh = delaunay.ToMesh();
        EXPECT_EQUIVALENT_USING(mesh.Vertices, zPolygon, TestHelper::Vertex2FNearlyEqual);
        EXPECT_EQUIVALENT_USING(mesh.Interior, std::vector<TriangleElement>({
            TriangleElement(0, 1, 2),
            TriangleElement(1, 3, 2),
        }), TestHelper::TriangleElementCyclicalEqual);
    }

    TEST(RefinedDelaunayTests, Refine_WhenPolygonIsComplex_ShouldResultRefinedDelaunay)
    {
        std::vector<Vertex2F> vertices({
            Vertex2F(-0.822222222f,  0.862222222f),
            Vertex2F(0.257777778f,  0.76f),
            Vertex2F(0.057777778f,  0.053333333f),
            Vertex2F(0.333333333f, -0.235555556f),
            Vertex2F(0.502222222f,  0.626666667f),
            Vertex2F(0.764444444f, -0.075555556f),
            Vertex2F(0.466666667f, -0.791111111f),
            Vertex2F(0.155555556f, -0.871111111f),
            Vertex2F(-0.177777778f, -0.866666667f),
            Vertex2F(-0.497777778f, -0.684444444f),
            Vertex2F(0.04f, -0.457777778f),
            Vertex2F(0.022222222f, -0.395555556f),
            Vertex2F(-0.773333333f, -0.035555556f),
        });
        PlanarStraightLineGraph graph;
        graph.AddClosedLineSegments(vertices);
        RefinedDelaunay delaunay = RefinedDelaunay::CreateTriangulation(graph);
        Mesh2D mesh = delaunay.ToMesh();
        
        EXPECT_EQUIVALENT_USING(mesh.Vertices, graph.GetVertices(), TestHelper::Vertex2FNearlyEqual);
        EXPECT_EQUIVALENT_USING(mesh.Interior, std::vector<TriangleElement>({
            TriangleElement(0, 2, 1), 
            TriangleElement(10, 6, 3), 
            TriangleElement(3, 6, 5), 
            TriangleElement(5, 2, 3), 
            TriangleElement(2, 4, 1), 
            TriangleElement(12, 2, 0), 
            TriangleElement(3, 11, 10), 
            TriangleElement(2, 5, 4), 
            TriangleElement(6, 10, 7), 
            TriangleElement(11, 3, 2),
            TriangleElement (9, 8, 10), 
            TriangleElement (7, 10, 8), 
            TriangleElement (12, 11, 2), 
            TriangleElement (9, 10, 11), 
            TriangleElement (11, 12, 9)
        }), TestHelper::TriangleElementCyclicalEqual);
        

        delaunay.Refine(7);
        mesh = delaunay.ToMesh();
        EXPECT_EQ(mesh.Vertices.size(), 19);
        EXPECT_EQUIVALENT_USING(mesh.Interior, std::vector<TriangleElement>({
            TriangleElement(12, 18, 0), 
            TriangleElement(10, 6, 3), 
            TriangleElement(15, 3, 6), 
            TriangleElement(13, 3, 5), 
            TriangleElement(4, 18, 13), 
            TriangleElement(18, 12, 2), 
            TriangleElement(3, 11, 10), 
            TriangleElement(3, 13, 2), 
            TriangleElement(6, 10, 7), 
            TriangleElement(11, 3, 2),
            TriangleElement(16, 8, 10), 
            TriangleElement(7, 10, 8), 
            TriangleElement(9, 17, 12), 
            TriangleElement(8, 16, 9), 
            TriangleElement(17, 9, 16), 
            TriangleElement(18, 4, 1), 
            TriangleElement(4, 13, 14), 
            TriangleElement(13, 5, 14), 
            TriangleElement(3, 15, 5), 
            TriangleElement(10, 11, 16),
            TriangleElement(17, 16, 11), 
            TriangleElement(11, 2, 17), 
            TriangleElement(2, 12, 17), 
            TriangleElement(13, 18, 2), 
            TriangleElement(1, 0, 18)
        }), TestHelper::TriangleElementCyclicalEqual);

    }


    static auto SmallAngleTestCases = ::testing::Values(
                                        std::make_tuple(6, 60, 60),
                                        std::make_tuple(12, 30, 30),
                                        std::make_tuple(20, 18, 31.717f),
                                        std::make_tuple(30, 12, 25.111f));

    class SmallAngleRefinementTests : public ::testing::TestWithParam<std::tuple<size_t, float, float>> {};

    TEST_P(SmallAngleRefinementTests, Refine_WhenAngleIsSmall_ShouldResultRefinedDelaunay) 
    {
        size_t n = std::get<0>(GetParam());
        float expectedAngleBefore = std::get<1>(GetParam());
        float expectedAngleAfter = std::get<2>(GetParam());

        float angle = 2.0f * M_PI / n;
        std::vector<Vertex2F> vertices(n);
        for(size_t i = 0; i < n; i++)
        {
            vertices[i] = Vertex2F(std::cos(i * angle), std::sin(i * angle));
        }

        PlanarStraightLineGraph graph;
        graph.AddClosedLineSegments(vertices);
        RefinedDelaunay delaunay = RefinedDelaunay::CreateTriangulation(graph);
        delaunay.InsertPoint(Vertex2F(0, 0));

        float smallestAngle = delaunay.GetSmallestAngleTriangle().GetSmallestAngle() * 180 / M_PI;
        EXPECT_NEAR(smallestAngle, expectedAngleBefore, 1e-3f);
        delaunay.Refine(25);

        smallestAngle = delaunay.GetSmallestAngleTriangle().GetSmallestAngle() * 180 / M_PI;
        EXPECT_NEAR(smallestAngle, expectedAngleAfter, 1e-3f);
    }

    INSTANTIATE_TEST_CASE_P(Refine_WhenAngleIsSmall_ShouldResultRefinedDelaunay, 
        SmallAngleRefinementTests, SmallAngleTestCases);
}