#pragma once

#include <Geometry/Structures/Mesh2D.hpp>
#include <Geometry/Structures/Vertex.hpp>
#include <LinearAlgebra/Matrix.hpp>
#include <LinearAlgebra/VectorBase.hpp>
#include <functional>
#include "FemAssembler.hpp"

/// <summary>
/// Helmholtz equation with source
/// dT/dt = k\nabla^2T
/// \nabla u = 0 on boundary
/// </summary>
class HeatEquationWithoutSource
{
private:
    Geometry::Mesh2D m_mesh;
    float m_k, m_dt;
    float m_time;

    LinearAlgebra::Matrix<float> m_massMatrix;
    LinearAlgebra::Matrix<float> m_stiffnessMatrix;
    LinearAlgebra::ColumnVector<float> m_currentSolution;

public:
    HeatEquationWithoutSource(const Geometry::Mesh2D& mesh, float k, float dt, FemAssembler::VertexValueFunc initialValues);

    const Geometry::Mesh2D& GetGraph() const { return m_mesh; }
    void SolveNextTimeStep();

    const LinearAlgebra::ColumnVector<float>& CurrentSolution() const { return m_currentSolution; }

    float CurrentTime() const { return m_time; }
};
