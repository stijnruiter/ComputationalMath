#pragma once

#include "FemAssembler.hpp"
#include <Geometry/Structures/Mesh2D.hpp>
#include <LinearAlgebra/Matrix.hpp>
#include <LinearAlgebra/VectorBase.hpp>

#include <future>

/// <summary>
/// Helmholtz equation with source
/// dT/dt = k\nabla^2T
/// \nabla u = 0 on boundary
/// </summary>
class HeatEquationWithoutSource
{
public:
    HeatEquationWithoutSource(const HeatEquationWithoutSource& other);
    HeatEquationWithoutSource(const Geometry::Mesh2D& mesh, float k, float dt, const FemAssembler::VertexValueFunc& initialValues);

    ~HeatEquationWithoutSource();

    const Geometry::Mesh2D& GetGraph() const { return m_mesh; }
    bool PollNextTimeStepReady();
    void StartComputation();

    const LinearAlgebra::ColumnVector<float>& CurrentSolution() const { return m_currentSolution; }

    float CurrentTime() const { return m_time; }

private:
    std::future<LinearAlgebra::ColumnVector<float>> CreateNextTimeStepComputationTask() const;
    std::future<LinearAlgebra::ColumnVector<float>> m_computeNextStepTask;
    Geometry::Mesh2D m_mesh;
    float m_k, m_dt;
    float m_time;

    LinearAlgebra::Matrix<float> m_massMatrix;
    LinearAlgebra::Matrix<float> m_stiffnessMatrix;
    LinearAlgebra::ColumnVector<float> m_currentSolution;
};
