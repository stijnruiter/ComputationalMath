#include "HalfEdgeTriangulation.h"
#include <cassert>

namespace Geometry
{
    HalfEdgeTriangulation::HalfEdgeTriangulation(size_t initialSize)
        : m_triangles(0), m_edges(0), m_elementCount(0), m_edgeCount(0)
    {
        m_triangles.reserve(initialSize);
        m_edges.reserve(initialSize * 3);
    }

    void HalfEdgeTriangulation::AddTriangle(size_t vertexIndex1, size_t vertexIndex2, size_t vertexIndex3)
    {
        size_t edgeIndex1 = m_elementCount;
        size_t edgeIndex2 = edgeIndex1 + 1;
        size_t edgeIndex3 = edgeIndex1 + 2;

        m_triangles.push_back(edgeIndex1);
        InsertEdge(vertexIndex1, vertexIndex2, edgeIndex1, edgeIndex3, edgeIndex2, m_elementCount);
        InsertEdge(vertexIndex2, vertexIndex3, edgeIndex2, edgeIndex1, edgeIndex3, m_elementCount);
        InsertEdge(vertexIndex3, vertexIndex1, edgeIndex3, edgeIndex2, edgeIndex1, m_elementCount);

        m_elementCount += 1;
        m_edgeCount += 3;
    }

    TriangleElement HalfEdgeTriangulation::GetTriangleVertices(size_t elementIndex) const
    {
        return GetTriangleVerticesFromEdge(m_triangles[elementIndex]);
    }

    TriangleElement HalfEdgeTriangulation::GetTriangleVerticesFromEdge(size_t edgeIndex) const
    {
        HalfEdge edge = m_edges[edgeIndex];
        return TriangleElement(edge.V1, edge.V2, m_edges[edge.NextEdge].V2);
    }

    const HalfEdge& HalfEdgeTriangulation::GetEdge(size_t edgeIndex) const
    {
        return m_edges[edgeIndex];
    }

    size_t HalfEdgeTriangulation::GetElementCount() const
    {
        return m_elementCount;
    }

    size_t HalfEdgeTriangulation::GetEdgeCount() const
    {
        return m_edgeCount;
    }

    bool HalfEdgeTriangulation::IsValidEdge(size_t edgeIndex) const
    {
        return edgeIndex < m_edgeCount;
    }

    Mesh2D HalfEdgeTriangulation::ToMesh() const
    {
        Mesh2D mesh(m_elementCount, 3);
        for (size_t i = 0; i < m_elementCount; i++)
        {
            HalfEdge edge1 = m_edges[m_triangles[i]];
            HalfEdge edge2 = m_edges[edge1.NextEdge];
            HalfEdge edge3 = m_edges[edge2.NextEdge];
            assert(edge3.NextEdge == m_triangles[i]);
            mesh.Interior.push_back(TriangleElement(edge1.V1, edge2.V1, edge3.V1));

            if(edge1.TwinEdge == size_t(-1)) { mesh.Boundary.push_back(LineElement(edge1.V1, edge1.V2)); }
            if(edge2.TwinEdge == size_t(-1)) { mesh.Boundary.push_back(LineElement(edge2.V1, edge2.V2)); }
            if(edge3.TwinEdge == size_t(-1)) { mesh.Boundary.push_back(LineElement(edge3.V1, edge3.V2)); }
        }
        return mesh;
    }

    void HalfEdgeTriangulation::InsertEdge(size_t vertexIndexStart, size_t vertexIndexEnd, size_t edgeIndex, size_t edgeIndexPrevious, size_t edgeIndexNext, size_t elementIndex)
    {
        size_t tmp;
        assert(GetEdgeIndex(vertexIndexStart, vertexIndexEnd, tmp) == false); // Edge already exists
        assert(edgeIndex == m_edges.size());
        
        size_t twinIndex;
        if (GetEdgeIndex(vertexIndexEnd, vertexIndexStart, twinIndex))
        {
            assert(m_edges[twinIndex].TwinEdge > m_edgeCount); // Twin already has a neighbour
            m_edges[twinIndex].TwinEdge = edgeIndex;
        }
        m_edges.push_back(HalfEdge(vertexIndexStart, vertexIndexEnd, edgeIndexPrevious, edgeIndexNext, twinIndex, elementIndex));
    }

    TriangleElement HalfEdgeTriangulation::RefineTriangle(size_t triangleIndex, size_t newVertexIndex)
    {
        // TODO: simplify/references
        size_t oldEdgeIndex1 = m_triangles[triangleIndex];
        HalfEdge oldEdge1 = m_edges[oldEdgeIndex1];
        
        size_t oldEdgeIndex2 = oldEdge1.NextEdge;
        HalfEdge oldEdge2 = m_edges[oldEdgeIndex2];
        
        size_t oldEdgeIndex3 = oldEdge2.NextEdge;
        HalfEdge oldEdge3 = m_edges[oldEdgeIndex3];
        
        assert(oldEdge1.PrevEdge == oldEdgeIndex3);
        assert(oldEdge3.NextEdge == oldEdgeIndex1);

        size_t newEdgeIndex1 = m_edgeCount;
        size_t newEdgeIndex2 = m_edgeCount + 1;
        size_t newEdgeIndex3 = m_edgeCount + 2;
        size_t newEdgeIndex4 = m_edgeCount + 3;
        size_t newEdgeIndex5 = m_edgeCount + 4;
        size_t newEdgeIndex6 = m_edgeCount + 5;

        // Replace "old" triangle with Triangle 1
        m_edges[oldEdgeIndex1] = HalfEdge(oldEdge1.V1, oldEdge1.V2, newEdgeIndex2, newEdgeIndex1, oldEdge1.TwinEdge, oldEdge1.ElementIndex);
        m_edges.push_back(HalfEdge(oldEdge1.V2, newVertexIndex, oldEdgeIndex1, newEdgeIndex2, newEdgeIndex4, oldEdge1.ElementIndex));
        m_edges.push_back(HalfEdge(newVertexIndex, oldEdge1.V1, newEdgeIndex1, oldEdgeIndex1, newEdgeIndex5, oldEdge1.ElementIndex));
        m_triangles[oldEdge1.ElementIndex] = oldEdgeIndex1;
        
        // Triangle 2
        m_edges[oldEdgeIndex2] = HalfEdge(oldEdge2.V1, oldEdge2.V2, newEdgeIndex4, newEdgeIndex3, oldEdge2.TwinEdge, m_elementCount);
        m_edges.push_back(HalfEdge(oldEdge2.V2, newVertexIndex, oldEdgeIndex2, newEdgeIndex4, newEdgeIndex6, m_elementCount));
        m_edges.push_back(HalfEdge(newVertexIndex, oldEdge2.V1, newEdgeIndex3, oldEdgeIndex2, newEdgeIndex1, m_elementCount));
        m_triangles.push_back(oldEdgeIndex2);
        
        // Triangle 3
        m_edges[oldEdgeIndex3] = HalfEdge(oldEdge3.V1, oldEdge3.V2, newEdgeIndex6, newEdgeIndex5, oldEdge3.TwinEdge, m_elementCount + 1);
        m_edges.push_back(HalfEdge(oldEdge3.V2, newVertexIndex, oldEdgeIndex3, newEdgeIndex6, newEdgeIndex2, m_elementCount + 1));
        m_edges.push_back(HalfEdge(newVertexIndex, oldEdge3.V1, newEdgeIndex5, oldEdgeIndex3, newEdgeIndex3, m_elementCount + 1));
        m_triangles.push_back(oldEdgeIndex3);

        m_elementCount += 2;
        m_edgeCount += 6;

        return TriangleElement(oldEdgeIndex1, oldEdgeIndex2, oldEdgeIndex3);
    }

    void HalfEdgeTriangulation::FlipEdge(size_t edgeIndex)
    {
        // TODO: optimize
        HalfEdge edge = m_edges[edgeIndex];
        size_t twinIndex = edge.TwinEdge;
        HalfEdge twin = m_edges[twinIndex];
        
        size_t previousEdgeIndex = edge.PrevEdge;
        size_t previousTwinIndex = twin.PrevEdge;
        size_t nextEdgeIndex = edge.NextEdge;
        size_t nextTwinIndex = twin.NextEdge;

        size_t edgeVertex = m_edges[nextEdgeIndex].V2;
        size_t twinVertex = m_edges[nextTwinIndex].V2;

        HalfEdge temp = m_edges[previousEdgeIndex]; 
        temp.PrevEdge = edgeIndex;
        temp.NextEdge = nextTwinIndex;
        temp.ElementIndex = edge.ElementIndex;
        m_edges[previousEdgeIndex] = temp;
        
        temp = m_edges[nextTwinIndex];
        temp.PrevEdge = previousEdgeIndex;
        temp.NextEdge = edgeIndex;
        temp.ElementIndex = edge.ElementIndex;
        m_edges[nextTwinIndex] = temp;
        
        m_edges[edgeIndex] = HalfEdge(twinVertex, edgeVertex, nextTwinIndex, previousEdgeIndex, twinIndex, edge.ElementIndex);
        m_triangles[edge.ElementIndex] = edgeIndex;

        temp = m_edges[previousTwinIndex];
        temp.PrevEdge = twinIndex;
        temp.NextEdge = nextEdgeIndex;
        temp.ElementIndex = twin.ElementIndex;
        m_edges[previousTwinIndex] = temp;

        temp = m_edges[nextEdgeIndex];
        temp.PrevEdge = previousTwinIndex;
        temp.NextEdge = twinIndex;
        temp.ElementIndex = twin.ElementIndex;
        m_edges[nextEdgeIndex] = temp;
        
        m_edges[twinIndex] = HalfEdge(edgeVertex, twinVertex, nextEdgeIndex, previousTwinIndex, edgeIndex, twin.ElementIndex);
        m_triangles[twin.ElementIndex] = twinIndex;
    }

    bool HalfEdgeTriangulation::GetEdgeIndex(size_t vStart, size_t vEnd, size_t& index) const
    {
        for (size_t i = 0; i < m_edgeCount; i++)
        {
            if (m_edges[i].V1 == vStart && m_edges[i].V2 == vEnd)
            {
                index = i;
                return true;
            }
        }

        return false; // MAX_SIZE
    }
}