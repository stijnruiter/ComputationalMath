#include "HelmholtzEquationWithSource.hpp"
#include "FemAssembler.hpp"
#include <cmath>

#include <LinearAlgebra/FactorizationLU.hpp>

ColumnVector<float> HelmholtzEquationWithSourceFEM::Solve() const
{
    return LinearAlgebra::Factorization::LUSolve(m_matrix, m_columnVector, 1e-5f);
}

float HelmholtzEquationWithSourceFEM::SourceFunction(Geometry::Vertex2F vertex) const
{
    return (m_k + std::pow(M_PI / m_bounds.GetWidth(), 2) + std::pow(M_PI / m_bounds.GetHeight(), 2)) * AnalyticSolutionFunction(vertex);
}

HelmholtzEquationWithSourceFEM::HelmholtzEquationWithSourceFEM(const Geometry::Rectangle& bounds, const Geometry::Mesh2D& mesh, float k)
    : m_mesh(mesh), m_bounds(bounds), m_k(k),
      m_matrix(FemAssembler::InitializeMatrix(mesh)),
      m_columnVector(FemAssembler::InitializeVector(mesh))
{
    FemAssembler::Add_Matrix_NablaA_NablaV(m_mesh, m_matrix, -1.0f);
    FemAssembler::Add_Matrix_U_V(m_mesh, m_matrix, m_k);
    FemAssembler::Add_Vector_U_F(m_mesh, m_columnVector, [this](Geometry::Vertex2F vertex)
                                 { return this->SourceFunction(vertex); });
}

float HelmholtzEquationWithSourceFEM::AnalyticSolutionFunction(Geometry::Vertex2F position) const
{
    float radX = M_PI * (position.X + m_bounds.Left) / m_bounds.GetWidth();
    float radY = M_PI * (position.Y + m_bounds.Bottom) / m_bounds.GetHeight();

    return std::cos(radX) * std::cos(radY);
}