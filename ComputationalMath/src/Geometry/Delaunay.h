#pragma once

#include <vector>
#include "Geometry/Structures/Vertex.h"
#include "Geometry/Structures/Triangle.h"
#include "Geometry/Structures/HalfEdgeTriangulation.h"
#include "Geometry/Structures/SimplexElements.h"

namespace Geometry
{
    class Delaunay
    {

    public:
        static Delaunay CreateTriangulation(const std::vector<Vertex2F>& vertices);
        
        void InsertPoint(Vertex2F point);

        Mesh2D ToMesh() const;

    private:
        Delaunay(Triangle boundingTriangle, int nVertexCapacity);
        
        size_t FindElement(Vertex2F point) const;

        void FlipTest(int edgeIndex);
        
        bool InCircle(size_t ai, size_t bi, size_t ci, size_t di) const;
        
        static float InCircleDeterminant(Vertex2F a, Vertex2F b, Vertex2F c, Vertex2F d);
    private: 
        std::vector<Vertex2F> m_vertices;
        HalfEdgeTriangulation m_triangulation;
    };
}