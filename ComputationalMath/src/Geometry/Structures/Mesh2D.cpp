#include "Mesh2D.h"

Geometry::Mesh2D::Mesh2D(size_t initialCapacityInterior, size_t initialCapacityBoundary)
    : Interior(0), Boundary(0), Vertices(0)
{
    Interior.reserve(initialCapacityInterior);
    Boundary.reserve(initialCapacityBoundary);
}

std::vector<Geometry::LineElement> Geometry::Mesh2D::GetAllEdges() const
{
    std::vector<Geometry::LineElement> result(0);
    result.reserve(Interior.size() * 3);
    for(const auto& element : Interior)
    {
        result.push_back(Geometry::LineElement(element.I, element.J));
        result.push_back(Geometry::LineElement(element.J, element.K));
        result.push_back(Geometry::LineElement(element.K, element.I));
    }
    return result;
}