#pragma once
#include <cstdint>

namespace Geometry
{
    struct HalfEdge
    {
        size_t V1;
        size_t V2;
        size_t PrevEdge;
        size_t NextEdge;
        size_t TwinEdge;
        size_t ElementIndex;

        HalfEdge() : V1(SIZE_MAX), V2(SIZE_MAX), PrevEdge(SIZE_MAX), NextEdge(SIZE_MAX), TwinEdge(SIZE_MAX), ElementIndex(SIZE_MAX)
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