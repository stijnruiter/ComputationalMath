#pragma once

#include <vector>
#include "HalfEdge.h"
#include "SimplexElements.h"
#include "Mesh2D.h"

namespace Geometry
{
    class HalfEdgeTriangulation
    {
    public:
        HalfEdgeTriangulation(size_t initialSize);

        void AddTriangle(size_t vertexIndex1, size_t vertexIndex2, size_t vertexIndex3);
        TriangleElement RefineTriangle(size_t triangleIndex, size_t newVertexIndex);
        void FlipEdge(size_t edgeIndex);

        TriangleElement GetTriangleVertices(size_t elementIndex) const;
        TriangleElement GetTriangleVerticesFromEdge(size_t edgeIndex) const;

        const HalfEdge& GetEdge(size_t edgeIndex) const;

        size_t GetElementCount() const;
        size_t GetEdgeCount() const;

        bool IsValidEdge(size_t edgeIndex) const;

        Mesh2D ToMesh() const;

    private: 
        void InsertEdge(size_t vertexIndexStart, size_t vertexIndexEnd, size_t edgeIndex, size_t edgeIndexPrevious, size_t edgeIndexNext, size_t elementIndex);
        bool GetEdgeIndex(size_t vStart, size_t vEnd, size_t& index) const;

    private:
        std::vector<HalfEdge> m_edges;
        std::vector<int> m_triangles;

        size_t m_elementCount;
        size_t m_edgeCount;
    };
}