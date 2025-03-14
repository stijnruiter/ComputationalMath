#include <gtest/gtest.h>
#include <Geometry/Delaunay.h>

#include "TestHelper.h"

namespace Geometry 
{
    static auto DelaunayDataSets = ::testing::Values(
        std::make_tuple(
            std::vector<Vertex2F>({
                Vertex2F(0.13375837f, -0.20463276f),
                Vertex2F(-0.0393703f, 0.3368733f),
                Vertex2F(-0.37653553f, 0.30180907f),
                Vertex2F(0.17102325f, -0.39327747f),
                Vertex2F(-0.1741004f, 0.5621339f)
            }),
            std::vector<TriangleElement>({
                TriangleElement(0, 2, 3),
                TriangleElement(1, 4, 2),
                TriangleElement(0, 1, 2),
            }),
            std::vector<LineElement>({
                LineElement(0, 1),
                LineElement(0, 3),
                LineElement(2, 3),
                LineElement(2, 4),
                LineElement(4, 1)
            })
        ),
        std::make_tuple(
            std::vector<Vertex2F>({
                Vertex2F(0.13375837f, -0.20463276f),
                Vertex2F(-0.0393703f, 0.3368733f),
                Vertex2F(-0.37653553f, 0.30180907f),
                Vertex2F(0.17102325f, -0.39327747f),
                Vertex2F(-0.1741004f, 0.5621339f),
                Vertex2F(0.7005063f, -0.49821767f),
                Vertex2F(0.6051475f, 0.061599255f),
                Vertex2F(0.50220823f, -0.20197105f),
                Vertex2F(0.17317522f, 0.010558367f),
                Vertex2F(0.58225656f, 0.36910498f),
                Vertex2F(-0.3951408f, 0.41237962f),
                Vertex2F(0.041640043f, -0.664723f),
                Vertex2F(0.26772082f, -0.35440302f),
                Vertex2F(0.13839245f, -0.19876397f),
                Vertex2F(0.25869608f, -0.67407477f),
                Vertex2F(-0.6667158f, -0.039070487f),
                Vertex2F(0.6294924f, 0.015692353f),
                Vertex2F(0.15297616f, 0.4711753f),
                Vertex2F(0.49639237f, -0.5018836f),
                Vertex2F(0.17881477f, -0.66860473f),
                Vertex2F(-0.031089962f, 0.3436073f),
                Vertex2F(0.51314855f, -0.15569323f),
                Vertex2F(-0.506284f, -0.48687214f),
                Vertex2F(0.31463242f, 0.5525198f),
                Vertex2F(-0.3399611f, 0.7265549f),
            }),
            std::vector<TriangleElement>({
                TriangleElement( 9, 16,  5),
                TriangleElement( 6,  9,  8),
                TriangleElement( 6, 16,  9),
                TriangleElement(10, 24, 15),
                TriangleElement( 2, 10, 15),
                TriangleElement(21,  6,  8),
                TriangleElement( 6, 21, 16),
                TriangleElement(16, 21,  5),
                TriangleElement(22,  0, 15),
                TriangleElement( 0,  2, 15),
                TriangleElement( 2,  0,  8),
                TriangleElement( 1,  2,  8),
                TriangleElement(20,  1,  8),
                TriangleElement(17, 20,  8),
                TriangleElement( 9, 17,  8),
                TriangleElement(23, 17,  9),
                TriangleElement(18, 14,  5),
                TriangleElement(14, 18, 12),
                TriangleElement(14, 19, 11),
                TriangleElement(13, 21,  8),
                TriangleElement( 0, 13,  8),
                TriangleElement(13,  0, 12),
                TriangleElement( 0,  3, 12),
                TriangleElement(19,  3, 11),
                TriangleElement( 3, 22, 11),
                TriangleElement( 3,  0, 22),
                TriangleElement( 3, 14, 12),
                TriangleElement( 3, 19, 14),
                TriangleElement(17,  4, 20),
                TriangleElement(10,  4, 24),
                TriangleElement( 4, 23, 24),
                TriangleElement( 4, 17, 23),
                TriangleElement( 4,  1, 20),
                TriangleElement( 4, 10,  2),
                TriangleElement( 1,  4,  2),
                TriangleElement( 7, 13, 12),
                TriangleElement(13,  7, 21),
                TriangleElement(18,  7, 12),
                TriangleElement(21,  7,  5),
                TriangleElement( 7, 18,  5),
            }),
            std::vector<LineElement>({
                LineElement(15, 24),
                LineElement(24, 23),
                LineElement(23, 9),
                LineElement(9, 5),
                LineElement(5, 14),
                LineElement(14, 11),
                LineElement(11, 22),
                LineElement(22, 15),
            })
        )
    );
    
    class DelaunayTriangulationByInsertionTests : public ::testing::TestWithParam<std::tuple<
        std::vector<Vertex2F>, 
        std::vector<TriangleElement>,
        std::vector<LineElement>>> {};

    TEST_P(DelaunayTriangulationByInsertionTests, CreateTriangulation_WhenVerticesCorrect_ShouldComputeDelaunayTriangulation) {
        std::vector<Vertex2F> vertices = std::get<0>(GetParam());
        std::vector<TriangleElement> expectedInterior = std::get<1>(GetParam());
        std::vector<LineElement> expectedBoundary = std::get<2>(GetParam());

        Mesh2D triangulation = Delaunay::CreateTriangulation(vertices).ToMesh();
        EXPECT_TRUE(TestHelper::AreEquivalent(triangulation.Interior, expectedInterior, TestHelper::TriangleElementCyclicalEqual));
        EXPECT_TRUE(TestHelper::AreEquivalent(triangulation.Boundary, expectedBoundary, TestHelper::LineElementCyclicalEqual));
    }
    INSTANTIATE_TEST_CASE_P(CreateTriangulation_WhenVerticesCorrect_ShouldComputeDelaunayTriangulation, 
        DelaunayTriangulationByInsertionTests, DelaunayDataSets);


}