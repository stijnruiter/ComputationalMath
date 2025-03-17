#pragma once

#include "Delaunay.hpp"
#include "Structures/PlanarStraightLineGraph.hpp"
#include "Structures/Triangle.hpp"

#include <math.h>
#include <stdexcept>

namespace Geometry
{
    /**
     * J. Ruppert, A Delaunay Refinement Algorithm for Quality 2-Dimensional Mesh Generation,
     * Journal of Algorithms, Volume 18, Issue 3, 1995, https://doi.org/10.1006/jagm.1995.1021.
     */
    class RefinedDelaunay : public Delaunay
    {
    public:
        PlanarStraightLineGraph graph;

    private:
        RefinedDelaunay(const PlanarStraightLineGraph& graph, Triangle boundingElement, int nVertexCapacity)
            : Delaunay(boundingElement, nVertexCapacity), graph(graph)
        {
        }

    public:
        static RefinedDelaunay CreateTriangulation(const PlanarStraightLineGraph& graph);

        void Refine(float alphaDegrees);
    };
}