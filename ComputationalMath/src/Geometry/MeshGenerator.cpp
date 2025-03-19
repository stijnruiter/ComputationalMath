#include "MeshGenerator.hpp"

#include "Geometry/RefinedDelaunay.hpp"
#include "Geometry/Structures/Mesh2D.hpp"
#include "Geometry/Structures/PlanarStraightLineGraph.hpp"
#include "Geometry/Structures/Rectangle.hpp"
#include <cmath>
#include <vector>

namespace Geometry
{

    Mesh2D CreateCircularMesh(float cx, float cy, float radius, float maxh)
    {
        Geometry::PlanarStraightLineGraph graph;
        int nPointsOnCircle = (int)std::ceil(M_PI / std::asin(0.5f * maxh / radius));
        nPointsOnCircle = nPointsOnCircle < 3 ? 3 : nPointsOnCircle;
        float angle = 2.0f * M_PI / nPointsOnCircle;
        std::vector<Geometry::Vertex2F> verticesOnCircle(nPointsOnCircle);
        float counter = 0.0f;
        for (size_t i = 0; i < nPointsOnCircle; i++)
        {
            verticesOnCircle[i] = Geometry::Vertex2F(cx + radius * std::cos(i * angle), cy + radius * std::sin(i * angle));
        }
        graph.AddClosedLineSegments(verticesOnCircle);
        Geometry::RefinedDelaunay delaunay = Geometry::RefinedDelaunay::CreateTriangulation(graph);
        delaunay.InsertPoint(Geometry::Vertex2F(cx, cy));
        delaunay.InsertPoint(Geometry::Vertex2F(cx + 0.1, cy));
        delaunay.InsertPoint(Geometry::Vertex2F(cx, cy + 0.1));
        delaunay.InsertPoint(Geometry::Vertex2F(cx - 0.1, cy));
        delaunay.InsertPoint(Geometry::Vertex2F(cx, cy - 0.1));
        delaunay.Refine(25);
        return delaunay.ToMesh();
    }

    Mesh2D CreateRectangularMesh(const Geometry::Rectangle& rect, unsigned int nx, unsigned int ny)
    {
        Mesh2D mesh;

        float dx = rect.GetWidth() / nx;
        float dy = rect.GetHeight() / ny;

        for (unsigned int j = 0; j <= ny; j++)
        {
            for (unsigned int i = 0; i <= nx; i++)
            {
                float x = rect.Left + dx * i;
                float y = rect.Bottom + dy * j;
                mesh.Vertices.push_back(Vertex2F(x, y));
            }
        }

        for (unsigned int j = 0; j < ny; j++)
        {
            for (unsigned int i = 0; i < nx; i++)
            {
                // 3--2
                // |  |
                // 0--1

                unsigned int corner0 = i + (nx + 1) * j;
                unsigned int corner1 = i + 1 + (nx + 1) * j;
                unsigned int corner2 = i + 1 + (nx + 1) * (j + 1);
                unsigned int corner3 = i + (nx + 1) * (j + 1);

                mesh.Interior.push_back(TriangleElement(corner0, corner1, corner2));
                mesh.Interior.push_back(TriangleElement(corner0, corner2, corner3));
            }
        }

        for (unsigned int i = 0; i < nx; i++)
        {
            mesh.Boundary.push_back(LineElement(i, i + 1));
            mesh.Boundary.push_back(LineElement(i + (nx + 1) * ny, i + 1 + (nx + 1) * ny));
        }

        for (unsigned int j = 0; j < ny; j++)
        {
            mesh.Boundary.push_back(LineElement((nx + 1) * j, (nx + 1) * (j + 1)));
            mesh.Boundary.push_back(LineElement((nx + 1) * j + nx, (nx + 1) * (j + 1) + nx));
        }

        return mesh;
    }
}