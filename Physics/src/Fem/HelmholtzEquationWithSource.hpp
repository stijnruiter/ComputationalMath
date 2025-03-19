#pragma once

#include <Geometry/Structures/Mesh2D.hpp>
#include <Geometry/Structures/Rectangle.hpp>
#include <LinearAlgebra/Matrix.hpp>
#include <LinearAlgebra/VectorBase.hpp>

/// <summary>
/// Helmholtz equation with source
/// -\nabla^2 u + u = f
/// \nabla u = 0 on boundary
/// f(x,y) =  cos(pi * (x - Bounds.Left) / Bounds.Width)) * cos(pi * (y - Bounds.Bottom) / Bounds.Height))
/// </summary>
class HelmholtzEquationWithSourceFEM
{
private:
    Geometry::Mesh2D m_mesh;
    Geometry::Rectangle m_bounds;
    float m_k;

    Matrix<float> m_matrix;
    ColumnVector<float> m_columnVector;

public:
    HelmholtzEquationWithSourceFEM(const Geometry::Rectangle& bounds, const Geometry::Mesh2D& mesh, float k);

    ColumnVector<float> Solve() const;
    float SourceFunction(Geometry::Vertex2F vertex) const;
    float AnalyticSolutionFunction(Geometry::Vertex2F position) const;
};
