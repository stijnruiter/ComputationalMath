#pragma once

#include "HalfEdge.hpp"
#include "Mesh2D.hpp"
#include "SimplexElements.hpp"
#include <vector>

namespace Geometry
{
    class HalfEdgeTriangulation
    {
    public:
        HalfEdgeTriangulation(unsigned int initialSize);

        void AddTriangle(unsigned int vertexIndex1, unsigned int vertexIndex2, unsigned int vertexIndex3);
        TriangleElement RefineTriangle(unsigned int triangleIndex, unsigned int newVertexIndex);
        void FlipEdge(unsigned int edgeIndex);

        TriangleElement GetTriangleElement(unsigned int elementIndex) const;
        TriangleElement GetTriangleElementFromEdge(unsigned int edgeIndex) const;

        const HalfEdge& GetEdge(unsigned int edgeIndex) const;

        unsigned int GetElementCount() const;
        unsigned int GetEdgeCount() const;

        bool IsValidEdge(unsigned int edgeIndex) const;

        Mesh2D ToMesh() const;

    private:
        void InsertEdge(unsigned int vertexIndexStart, unsigned int vertexIndexEnd, unsigned int edgeIndex, unsigned int edgeIndexPrevious, unsigned int edgeIndexNext, unsigned int elementIndex);
        bool GetEdgeIndex(unsigned int vStart, unsigned int vEnd, unsigned int& index) const;

    private:
        std::vector<HalfEdge> m_edges;
        std::vector<int> m_triangles;

        unsigned int m_elementCount;
        unsigned int m_edgeCount;
    };
}