#include "HeatEquationWithoutSource.hpp"
#include "FemAssembler.hpp"
#include <LinearAlgebra/FactorizationLU.hpp>

HeatEquationWithoutSource::HeatEquationWithoutSource(const Geometry::Mesh2D& mesh, float k, float dt, FemAssembler::VertexValueFunc initialValues)
    : m_mesh(mesh), m_k(k), m_dt(dt), m_time(0),
      m_massMatrix(FemAssembler::InitializeMatrix(mesh)),
      m_stiffnessMatrix(FemAssembler::InitializeMatrix(mesh)),
      m_currentSolution(FemAssembler::InitializeVector(mesh, initialValues))
{
    FemAssembler::Add_Matrix_U_V(mesh, m_massMatrix, 1.0f);
    FemAssembler::Add_Matrix_NablaA_NablaV(mesh, m_stiffnessMatrix, 1.0f * m_k);
}

void HeatEquationWithoutSource::SolveNextTimeStep()
{
    m_currentSolution =
        LinearAlgebra::Factorization::LUSolve(m_massMatrix + m_stiffnessMatrix * m_dt, 
            m_massMatrix * m_currentSolution, 1e-6f);
    m_time += m_dt;
}
