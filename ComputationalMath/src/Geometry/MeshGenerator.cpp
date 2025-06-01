#include "MeshGenerator.hpp"

#include "Geometry/RefinedDelaunay.hpp"
#include "Geometry/Structures/Mesh2D.hpp"
#include "Geometry/Structures/PlanarStraightLineGraph.hpp"
#include "Geometry/Structures/Rectangle.hpp"
#include <cmath>
#include <vector>

namespace Geometry
{
    Mesh2D CreateCircularMesh(const float cx, const float cy, const float radius, const float maxh)
    {
        PlanarStraightLineGraph graph;
        int nPointsOnCircle = static_cast<int>(std::ceil(M_PI / std::asin(0.5f * maxh / radius)));
        nPointsOnCircle = nPointsOnCircle < 3 ? 3 : nPointsOnCircle;
        const float angle = 2.0f * M_PI / nPointsOnCircle;
        std::vector<Vertex2F> verticesOnCircle(nPointsOnCircle);
        for (size_t i = 0; i < nPointsOnCircle; i++)
        {
            verticesOnCircle[i] = Vertex2F(cx + radius * std::cos(i * angle), cy + radius * std::sin(i * angle));
        }
        graph.AddClosedLineSegments(verticesOnCircle);
        RefinedDelaunay delaunay = RefinedDelaunay::CreateTriangulation(graph);
        delaunay.InsertPoint(Vertex2F(cx, cy));
        delaunay.InsertPoint(Vertex2F(cx + 0.1, cy));
        delaunay.InsertPoint(Vertex2F(cx, cy + 0.1));
        delaunay.InsertPoint(Vertex2F(cx - 0.1, cy));
        delaunay.InsertPoint(Vertex2F(cx, cy - 0.1));
        delaunay.Refine(25);
        return delaunay.ToMesh();
    }

    Mesh2D CreateRectangularMesh(const Rectangle& rect, const unsigned int nx, const unsigned int ny)
    {
        Mesh2D mesh;

        const float dx = rect.GetWidth() / nx;
        const float dy = rect.GetHeight() / ny;

        for (unsigned int j = 0; j <= ny; j++)
        {
            for (unsigned int i = 0; i <= nx; i++)
            {
                const float x = rect.Left + dx * i;
                const float y = rect.Bottom + dy * j;
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

                const unsigned int corner0 = i + (nx + 1) * j;
                const unsigned int corner1 = i + 1 + (nx + 1) * j;
                const unsigned int corner2 = i + 1 + (nx + 1) * (j + 1);
                const unsigned int corner3 = i + (nx + 1) * (j + 1);

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