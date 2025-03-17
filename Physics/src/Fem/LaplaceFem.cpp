#include "LaplaceFem.hpp"

LaplaceFem::LaplaceFem(const Geometry::Rectangle& bounds, const Geometry::Mesh2D& mesh) 
    : FemProblem2dBase(mesh), m_bounds(bounds)
{
    Add_Matrix_NablaA_NablaV(1.0f);

    ApplyNaturalBoundaryConditions([this](Geometry::Vertex2F vertex1, Geometry::Vertex2F vertex2)
                                   { return this->NaturalBoundaryCondition(vertex1, vertex2); });
    ApplyEssentialBoundaryCondition([this](Geometry::Vertex2F vertex, float& value)
                                    { return this->EssentialBoundaryCondition(vertex, value); });
}

float LaplaceFem::NaturalBoundaryCondition(Geometry::Vertex2F vertex1, Geometry::Vertex2F vertex2)
{
    // dU/dn = \nabla Y * n = (0, 1) * n
    if (vertex1.Y == vertex2.Y && vertex1.Y == m_bounds.Bottom) // n = (0, -1)
        return -1.0f;

    if (vertex1.Y == vertex2.Y && vertex1.Y == m_bounds.Top) // n = (0, 1)
        return 1.0f;

    return 0.0f; // n = (1, 0) || (-1, 0)
}
bool LaplaceFem::EssentialBoundaryCondition(Geometry::Vertex2F vertex1, float& result)
{
    result = vertex1.Y;
    return (vertex1.X == m_bounds.Left || vertex1.X == m_bounds.Right);
}

float LaplaceFem::AnalyticSolutionFunction(Geometry::Vertex2F position) const
{
    return position.Y;
}