#pragma once

#include "Geometry/Structures/HalfEdgeTriangulation.hpp"
#include "Geometry/Structures/SimplexElements.hpp"
#include "Geometry/Structures/Triangle.hpp"
#include "Geometry/Structures/Vertex.hpp"
#include <vector>

namespace Geometry
{
    class Delaunay
    {

    public:
        static Delaunay CreateTriangulation(const std::vector<Vertex2F>& vertices);

        void InsertPoint(Vertex2F point);

        Mesh2D ToMesh() const;

        Triangle GetSmallestAngleTriangle() const;

    protected:
        inline Triangle GetTriangle(TriangleElement element) const;

        Delaunay(Triangle boundingTriangle, int nVertexCapacity);

        unsigned int FindElement(Vertex2F point) const;

        void FlipTest(int edgeIndex);

        inline bool InCircle(unsigned int ai, unsigned int bi, unsigned int ci, unsigned int di) const;

        static inline float InCircleDeterminant(Vertex2F a, Vertex2F b, Vertex2F c, Vertex2F d);

    private:
        std::vector<Vertex2F> m_vertices;
        HalfEdgeTriangulation m_triangulation;
    };
}