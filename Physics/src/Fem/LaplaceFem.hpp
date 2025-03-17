#pragma once
#include "FemProblem2DBase.hpp"
#include "math.h"
#include <Geometry/Structures/Rectangle.hpp>
/// <summary>
/// Very unnatural problem, but just to combine Dirichlet and Neumann Boundary conditions
/// \nabla^2 u = 0
/// u(Bounds.Left, y) = u(Bounds.Right, y) = y
/// du/dy(x, Bounds.Bottom) = du/dy(x, Bounds.Top) = 1
/// </summary>
class LaplaceFem : public FemProblem2dBase
{
private:
    Geometry::Rectangle m_bounds;

public:
    LaplaceFem(const Geometry::Rectangle& bounds, const Geometry::Mesh2D& mesh);

    float NaturalBoundaryCondition(Geometry::Vertex2F vertex1, Geometry::Vertex2F vertex2);

    bool EssentialBoundaryCondition(Geometry::Vertex2F vertex1, float& result);

    float AnalyticSolutionFunction(Geometry::Vertex2F position) const;
};
