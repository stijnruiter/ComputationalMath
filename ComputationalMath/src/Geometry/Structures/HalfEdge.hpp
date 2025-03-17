#pragma once
#include <climits>

namespace Geometry
{
    struct HalfEdge
    {
        unsigned int V1;
        unsigned int V2;
        unsigned int PrevEdge;
        unsigned int NextEdge;
        unsigned int TwinEdge;
        unsigned int ElementIndex;

        HalfEdge() : V1(UINT_MAX), V2(UINT_MAX), PrevEdge(UINT_MAX), NextEdge(UINT_MAX), TwinEdge(UINT_MAX), ElementIndex(UINT_MAX)
        {
        }

        HalfEdge(unsigned int v1, unsigned int v2, unsigned int prevEdge, unsigned int nextEdge, unsigned int twinEdge, unsigned int elementIndex)
            : V1(v1), V2(v2), PrevEdge(prevEdge), NextEdge(nextEdge), TwinEdge(twinEdge), ElementIndex(elementIndex)
        {
        }

        HalfEdge(const HalfEdge& edge)
            : V1(edge.V1), V2(edge.V2), PrevEdge(edge.PrevEdge), NextEdge(edge.NextEdge), TwinEdge(edge.TwinEdge), ElementIndex(edge.ElementIndex)
        {
        }
    };
}