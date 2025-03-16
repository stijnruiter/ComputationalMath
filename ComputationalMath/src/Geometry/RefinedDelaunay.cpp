#include "RefinedDelaunay.h"

namespace Geometry
{
    RefinedDelaunay Geometry::RefinedDelaunay::CreateTriangulation(const PlanarStraightLineGraph &graph)
    {
        if(graph.GetVertexCount() <= 3)
            throw std::invalid_argument("Graph is empty.");
        
        RefinedDelaunay delaunay = RefinedDelaunay(graph, Triangle::ContainingTriangle(graph.GetVertices(), 1e5f), graph.GetVertexCount());
        for (const Vertex2F& vertex : graph.GetVertices())
        {
            delaunay.InsertPoint(vertex);
        }
        
        return delaunay;
    }
    
    void RefinedDelaunay::Refine(float alphaDegrees)
    {
        float alphaRadians = alphaDegrees * M_PI / 180;
        while(true)
        {
            const std::vector<LineElement>& segments = graph.GetLineSegments();
            const std::vector<Vertex2F>& vertices = graph.GetVertices();
            for (int i = 0; i < segments.size(); i++)
            {
                LineElement segment = segments[i];
                Vertex2F v1 = vertices[segment.I];
                Vertex2F v2 = vertices[segment.J];

                Vertex2F mid = 0.5f * (v1 + v2);
                float radius = Vertex2F::Distance(v1, mid) - 1e-3f; // TODO: more robust implementation to ignore v1 and v2
                if (graph.AnyVertexWithinRange(mid, radius))
                {
                    InsertPoint(mid);
                    graph.SplitLineSegment(i);
                    i--;
                }
            }

            Triangle smallestTriangle = GetSmallestAngleTriangle();
            Vertex2F circumCenter = smallestTriangle.GetCirclumcenter();
            float angle = smallestTriangle.GetSmallestAngle();

            if (angle >= alphaRadians)
                return;

            bool circumcenterEncroached = false;
            for (size_t i = 0; i < segments.size(); i++)
            {
                LineElement segment = segments[i];
                Vertex2F v1 = vertices[segment.I];
                Vertex2F v2 = vertices[segment.J];

                Vertex2F mid = 0.5f * (v1 + v2);
                float radius = Vertex2F::Distance(v1, mid) - 1e-3f; // TODO: more robust implementation to ignore v1 and v2
                if (Vertex2F::Distance(circumCenter, mid) < radius)
                {
                    InsertPoint(mid);
                    graph.SplitLineSegment(i);
                    i--;
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