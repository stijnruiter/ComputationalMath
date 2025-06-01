#include "LaplaceFem.hpp"
#include "FemAssembler.hpp"
#include <LinearAlgebra/FactorizationLU.hpp>

LaplaceFem::LaplaceFem(const Geometry::Rectangle& bounds, const Geometry::Mesh2D& mesh)
    : m_mesh(mesh), m_bounds(bounds),
      m_matrix(FemAssembler::InitializeMatrix(mesh)),
      m_columnVector(FemAssembler::InitializeVector(mesh))
{
    FemAssembler::Add_Matrix_NablaA_NablaV(m_mesh, m_matrix, 1.0f);

    FemAssembler::AddNaturalBoundaryConditions(m_mesh, m_columnVector,
                                               [this](Geometry::Vertex2F vertex1, Geometry::Vertex2F vertex2)
                                               { return this->NaturalBoundaryCondition(vertex1, vertex2); });

    FemAssembler::ApplyEssentialBoundaryCondition(m_mesh, m_matrix, m_columnVector,
                                                  [this](Geometry::Vertex2F vertex, float& value)
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

LinearAlgebra::ColumnVector<float> LaplaceFem::Solve() const
{
    return LinearAlgebra::Factorization::LUSolve(m_matrix, m_columnVector, 1e-5f);
}
