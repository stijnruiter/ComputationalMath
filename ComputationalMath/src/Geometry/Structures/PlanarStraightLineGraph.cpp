#include "PlanarStraightLineGraph.h"
#include <stdexcept>
#include <cassert>
#include <climits>

namespace Geometry
{
    PlanarStraightLineGraph::PlanarStraightLineGraph() { }

    void PlanarStraightLineGraph::AddLineSegment(Vertex2F start, Vertex2F end)
    {
        m_vertices.push_back(start);
        m_vertices.push_back(end);
        m_segments.push_back(LineElement(m_vertices.size() - 2, m_vertices.size() - 1));
    }

    void PlanarStraightLineGraph::AddLineSegments(std::vector<Vertex2F> polygon)
    {
        assert(polygon.size() < UINT_MAX);
        assert(m_vertices.size() + polygon.size() < UINT_MAX);
        unsigned int polygonLength = polygon.size();
        if (polygonLength <= 1)
            throw std::invalid_argument("The polygon must have at least two vertices.");

        unsigned int currentLength = m_vertices.size();
        for(unsigned int i = currentLength; i < currentLength + polygonLength - 1; i++)
        {
            m_segments.push_back(LineElement(i, i + 1));
        }

        for (auto const& i : polygon) 
        {
            m_vertices.push_back(i);
        }
    }

    void PlanarStraightLineGraph::AddClosedLineSegments(std::vector<Vertex2F> polygon)
    {
        AddLineSegments(polygon);
        // Connect the last vertex to the first vertex to close the polygon loop
        assert(m_vertices.size() < UINT_MAX);
        m_segments.push_back(LineElement(m_vertices.size() - 1, m_vertices.size() - polygon.size()));
    }

    void PlanarStraightLineGraph::RemoveLineSegment(unsigned int lineSegmentIndex)
    {
        if (lineSegmentIndex >= m_segments.size())
            throw std::out_of_range("Index out of range");

        m_segments.erase(m_segments.begin() + lineSegmentIndex);
    }

    void PlanarStraightLineGraph::SplitLineSegment(int lineSegmentIndex, float alpha)
    {
        LineElement lineSegment = m_segments[lineSegmentIndex];
        Vertex2F startVertex = m_vertices[lineSegment.I];
        Vertex2F endVertex = m_vertices[lineSegment.J];
        
        size_t splitVertexIndex = m_vertices.size();
        Vertex2F splitVertex = startVertex + alpha * (endVertex - startVertex);
        
        m_vertices.push_back(splitVertex);

        RemoveLineSegment(lineSegmentIndex);
        m_segments.push_back(LineElement(lineSegment.I, splitVertexIndex));
        m_segments.push_back(LineElement(splitVertexIndex, lineSegment.J));
    }

    unsigned int PlanarStraightLineGraph::GetVertexCount() const
    {
        assert(m_vertices.size() < UINT_MAX);
        return m_vertices.size();
    }

    const std::vector<Vertex2F> &PlanarStraightLineGraph::GetVertices() const
    {
        return m_vertices;
    }
    
    const std::vector<LineElement> &PlanarStraightLineGraph::GetLineSegments() const
    {
        return m_segments;
    }
    
    bool PlanarStraightLineGraph::AnyVertexWithinRange(Vertex2F vertex, float distance) const
    {
        for (const Vertex2F& p : m_vertices)
        {
            if (vertex.DistanceTo(p) < distance)
                return true;
        }
        return false;
    }
}