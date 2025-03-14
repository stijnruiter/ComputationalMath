#pragma once

#include "Vertex.h"
#include "SimplexElements.h"
#include <vector>

namespace Geometry
{
    class PlanarStraightLineGraph
    {
    public:

        PlanarStraightLineGraph();

        void AddLineSegment(Vertex2F start, Vertex2F end);

        void AddLineSegments(std::vector<Vertex2F> polygon);
        
        void AddClosedLineSegments(std::vector<Vertex2F> polygon);
        
        void RemoveLineSegment(size_t lineSegmentIndex);
        
        void SplitLineSegment(int lineSegmentIndex, float alpha = 0.5f);

        size_t GetVertexCount() const;

        const std::vector<Vertex2F>& GetVertices() const;
        const std::vector<LineElement>& GetLineSegments() const;

        bool AnyVertexWithinRange(Vertex2F vertex, float distance) const;

    private:
        std::vector<Vertex2F> m_vertices;
        std::vector<LineElement> m_segments;
    };
}