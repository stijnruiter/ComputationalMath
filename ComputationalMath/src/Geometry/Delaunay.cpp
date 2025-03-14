#include "Delaunay.h"
#include <stdexcept>
#include "LinearAlgebra/Matrix.h"

namespace Geometry
{
    Delaunay::Delaunay(Triangle boundingTriangle, int nVertexCapacity)
        : m_vertices(0), 
        m_triangulation(2 * nVertexCapacity + 7) // 2 * nTriangles + 1 = 2 * (nVertexCapacity + 3) + 1
    {
        m_vertices.reserve(nVertexCapacity + 3);
        m_vertices.push_back(boundingTriangle.V1);
        m_vertices.push_back(boundingTriangle.V2);
        m_vertices.push_back(boundingTriangle.V3);
        m_triangulation.AddTriangle(0, 1, 2);
    }

    Delaunay Delaunay::CreateTriangulation(const std::vector<Vertex2F> &vertices)
    {
        Delaunay delaunay(Triangle::ContainingTriangle(vertices, 1e5f), vertices.size());
        for (const Vertex2F& vertex : vertices)
        {
            delaunay.InsertPoint(vertex);
        }
        return delaunay;
    }

    void Delaunay::InsertPoint(Vertex2F point)
    {
        size_t indexP = m_vertices.size();
        m_vertices.push_back(point);
        size_t elementIndex = FindElement(point);
        TriangleElement edges = m_triangulation.RefineTriangle(elementIndex, indexP);
        FlipTest(edges.I);
        FlipTest(edges.J);
        FlipTest(edges.K);
    }

    Mesh2D Delaunay::ToMesh() const
    {
        Mesh2D mesh = m_triangulation.ToMesh();
        mesh.Boundary.clear();
        size_t initialSize = mesh.Interior.size();
        for (size_t i = initialSize - 1; i <= initialSize; i--) // Break on overflow
        {
            TriangleElement& element = mesh.Interior[i];
            if (element.I < 3)
            {
                if (element.J >= 3 && element.K >= 3)
                {
                    mesh.Boundary.push_back(LineElement(element.J - 3, element.K - 3));
                }
                mesh.Interior.erase(mesh.Interior.begin() + i);
            }
            else if (element.J < 3)
            {
                if (element.K >= 3)
                {
                    mesh.Boundary.push_back(LineElement(element.K - 3, element.I - 3));
                }
                mesh.Interior.erase(mesh.Interior.begin() + i);
            }
            else if (element.K < 3)
            {
                mesh.Boundary.push_back(LineElement(element.I - 3, element.J - 3));
                mesh.Interior.erase(mesh.Interior.begin() + i);
            }
            else
            {
                mesh.Interior[i] = TriangleElement(element.I - 3, element.J - 3, element.K - 3);
            }
        }
        return mesh;
    }

    size_t Delaunay::FindElement(Vertex2F point) const
    {
        for (size_t i = 0; i < m_triangulation.GetElementCount(); i++)
        {
            TriangleElement indices = m_triangulation.GetTriangleVertices(i);
            if (Triangle::ContainsVertex(point, m_vertices[indices.I], m_vertices[indices.J], m_vertices[indices.K]))
                return i;
        }
        
        throw std::invalid_argument("Point not inside triangulation.");
    }

    void Delaunay::FlipTest(int edgeIndex)
    {
        const HalfEdge& edge = m_triangulation.GetEdge(edgeIndex);
        if (!m_triangulation.IsValidEdge(edge.TwinEdge))
            return;

        HalfEdge twinEdge = m_triangulation.GetEdge(edge.TwinEdge);

        size_t triangleThirdVertex = m_triangulation.GetEdge(edge.NextEdge).V2;
        size_t twinTriangleThirdVertex = m_triangulation.GetEdge(twinEdge.NextEdge).V2;

        if (!InCircle(edge.V2, triangleThirdVertex, edge.V1, twinTriangleThirdVertex))
            return;

        m_triangulation.FlipEdge(edgeIndex);

        FlipTest(twinEdge.NextEdge);
        FlipTest(twinEdge.PrevEdge);
    }

    bool Delaunay::InCircle(size_t ai, size_t bi, size_t ci, size_t di) const
    {
        return InCircleDeterminant(m_vertices[ai], m_vertices[bi], m_vertices[ci], m_vertices[di]) > 0;
    }

    float Delaunay::InCircleDeterminant(Vertex2F a, Vertex2F b, Vertex2F c, Vertex2F d)
    {
        /**
         * For triangle abc (order counter clockwise), the point d is inside circumcircle if det M > 0
         * M = 
         * | Ax Ay Ax**2 + Ay**2 1 |
         * | Bx By Bx**2 + By**2 1 |
         * | Cx Cy Cx**2 + Cy**2 1 |
         * | Dx Dy Dx**2 + Dy**2 1 |
         */

        float aLengthSquared = a.LengthSquared();
        float bLengthSquared = b.LengthSquared();
        float cLengthSquared = c.LengthSquared();
        float dLengthSquared = d.LengthSquared();
        return a.X * Matrix<float>::Determinant(b.Y, bLengthSquared, 1, c.Y, cLengthSquared, 1, d.Y, dLengthSquared, 1)
            - a.Y * Matrix<float>::Determinant(b.X, bLengthSquared, 1, c.X, cLengthSquared, 1, d.X, dLengthSquared, 1)
            + aLengthSquared * Matrix<float>::Determinant(b.X, b.Y, 1, c.X, c.Y, 1, d.X, d.Y, 1)
            - Matrix<float>::Determinant(b.X, b.Y, bLengthSquared, c.X, c.Y, cLengthSquared, d.X, d.Y, dLengthSquared);
    }

}