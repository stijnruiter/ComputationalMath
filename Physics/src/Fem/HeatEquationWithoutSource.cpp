#include "HeatEquationWithoutSource.hpp"
#include "FemAssembler.hpp"
#include <LinearAlgebra/FactorizationLU.hpp>
#include <future>

HeatEquationWithoutSource::HeatEquationWithoutSource(const HeatEquationWithoutSource& other)
    : m_mesh(other.m_mesh), m_k(other.m_k), m_dt(other.m_dt),
      m_time(other.m_time),
      m_massMatrix(other.m_massMatrix),
      m_stiffnessMatrix(other.m_stiffnessMatrix),
      m_currentSolution(other.m_currentSolution)
{
}

HeatEquationWithoutSource::HeatEquationWithoutSource(const Geometry::Mesh2D& mesh, const float k, const float dt, const FemAssembler::VertexValueFunc& initialValues)
    : m_mesh(mesh), m_k(k), m_dt(dt), m_time(0),
      m_massMatrix(FemAssembler::InitializeMatrix(mesh)),
      m_stiffnessMatrix(FemAssembler::InitializeMatrix(mesh)),
      m_currentSolution(FemAssembler::InitializeVector(mesh, initialValues))
{
    FemAssembler::Add_Matrix_U_V(mesh, m_massMatrix, 1.0f);
    FemAssembler::Add_Matrix_NablaA_NablaV(mesh, m_stiffnessMatrix, 1.0f * m_k);
}

bool HeatEquationWithoutSource::PollNextTimeStepReady()
{
    if (!m_computeNextStepTask.valid())
    {
        m_computeNextStepTask = CreateNextTimeStepComputationTask();
    }

    if (m_computeNextStepTask.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
    {
        m_currentSolution = m_computeNextStepTask.get();
        m_time += m_dt;
        m_computeNextStepTask = CreateNextTimeStepComputationTask();
        return true;
    }

    return false;
}
void HeatEquationWithoutSource::StartComputation()
{
    PollNextTimeStepReady();
}

HeatEquationWithoutSource::~HeatEquationWithoutSource()
{
    if (m_computeNextStepTask.valid())
    {
        // Wait for any background computations before destruction
        // TODO: implement better way to destruct. Avoid deadlocks..
        m_computeNextStepTask.wait();
    }
}

std::future<LinearAlgebra::ColumnVector<float>> HeatEquationWithoutSource::CreateNextTimeStepComputationTask() const
{
    return std::async([this]
                      { return LinearAlgebra::Factorization::LUSolve(m_massMatrix + m_stiffnessMatrix * m_dt,
                                                                     m_massMatrix * m_currentSolution, 1e-6f); });
}