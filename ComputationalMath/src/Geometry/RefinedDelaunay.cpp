#include "RefinedDelaunay.hpp"
#include <cassert>
#include <climits>
#include <math.h>

namespace Geometry
{
    RefinedDelaunay RefinedDelaunay::CreateTriangulation(const PlanarStraightLineGraph& graph)
    {
        if (graph.GetVertexCount() <= 3)
            throw std::invalid_argument("Graph is empty.");

        auto delaunay = RefinedDelaunay(graph, Triangle::ContainingTriangle(graph.GetVertices(), 1e5f), graph.GetVertexCount());
        for (const Vertex2F& vertex : graph.GetVertices())
        {
            delaunay.InsertPoint(vertex);
        }

        return delaunay;
    }

    void RefinedDelaunay::Refine(const float alphaDegrees)
    {
        const float alphaRadians = alphaDegrees * M_PI / 180;
        while (true)
        {
            const std::vector<LineElement>& segments = graph.GetLineSegments();
            const std::vector<Vertex2F>& vertices = graph.GetVertices();
            for (int i = 0; i < segments.size(); i++)
            {
                const LineElement segment = segments[i];
                const Vertex2F v1 = vertices[segment.I];
                const Vertex2F v2 = vertices[segment.J];

                const Vertex2F mid = 0.5f * (v1 + v2);
                if (const float radius = Vertex2F::Distance(v1, mid) - 1e-3f; graph.AnyVertexWithinRange(mid, radius))
                {
                    InsertPoint(mid);
                    graph.SplitLineSegment(i);
                    --i;
                }
            }

            const Triangle smallestTriangle = GetSmallestAngleTriangle();
            const Vertex2F circumCenter = smallestTriangle.GetCirclumcenter();

            if (const float angle = smallestTriangle.GetSmallestAngle(); angle >= alphaRadians)
                return;

            bool circumcenterEncroached = false;
            assert(segments.size() < UINT_MAX);
            for (unsigned int i = 0; i < segments.size(); i++)
            {
                const LineElement segment = segments[i];
                const Vertex2F v1 = vertices[segment.I];
                const Vertex2F v2 = vertices[segment.J];

                const Vertex2F mid = 0.5f * (v1 + v2);
                if (const float radius = Vertex2F::Distance(v1, mid) - 1e-3f; Vertex2F::Distance(circumCenter, mid) < radius)
                {
                    InsertPoint(mid);
                    graph.SplitLineSegment(i);
                    --i;
                    circumcenterEncroached = true;
                }
            }

            if (!circumcenterEncroached)
            {
                InsertPoint(circumCenter);
            }
        }
    }
}