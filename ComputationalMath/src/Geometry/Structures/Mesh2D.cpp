#include "Mesh2D.hpp"

Geometry::Mesh2D::Mesh2D(const size_t initialCapacityInterior, const size_t initialCapacityBoundary)
    : Vertices(0), Interior(0), Boundary(0)
{
    Interior.reserve(initialCapacityInterior);
    Boundary.reserve(initialCapacityBoundary);
}

std::vector<Geometry::LineElement> Geometry::Mesh2D::GetAllEdges() const
{
    std::vector<LineElement> result(0);
    result.reserve(Interior.size() * 3);
    for (const auto& element : Interior)
    {
        result.push_back(LineElement(element.I, element.J));
        result.push_back(LineElement(element.J, element.K));
        result.push_back(LineElement(element.K, element.I));
    }
    return result;
}