#pragma once

#include <Geometry/Structures/Mesh2D.hpp>
#include <Geometry/Structures/Rectangle.hpp>
#include <LinearAlgebra/Matrix.hpp>
#include <LinearAlgebra/VectorBase.hpp>
/// <summary>
/// Very unnatural problem, but just to combine Dirichlet and Neumann Boundary conditions
/// \nabla^2 u = 0
/// u(Bounds.Left, y) = u(Bounds.Right, y) = y
/// du/dy(x, Bounds.Bottom) = du/dy(x, Bounds.Top) = 1
/// </summary>
class LaplaceFem
{
public:
    LaplaceFem(const Geometry::Rectangle& bounds, const Geometry::Mesh2D& mesh);

    float NaturalBoundaryCondition(Geometry::Vertex2F vertex1, Geometry::Vertex2F vertex2) const;

    bool EssentialBoundaryCondition(Geometry::Vertex2F vertex1, float& result) const;

    float AnalyticSolutionFunction(Geometry::Vertex2F position) const;

    LinearAlgebra::ColumnVector<float> Solve() const;

private:
    Geometry::Mesh2D m_mesh;
    Geometry::Rectangle m_bounds;
    LinearAlgebra::Matrix<float> m_matrix;
    LinearAlgebra::ColumnVector<float> m_columnVector;

};
