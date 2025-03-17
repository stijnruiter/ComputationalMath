#pragma once
#include "Geometry/Structures/Mesh2D.hpp"
#include "Geometry/Structures/Rectangle.hpp"
#include <vector>

namespace Geometry
{
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