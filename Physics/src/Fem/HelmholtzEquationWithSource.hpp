#pragma once

#include "FemProblem2DBase.hpp"
#include <Geometry/Structures/Rectangle.hpp>

/// <summary>
/// Helmholtz equation with source
/// -\nabla^2 u + u = f
/// \nabla u = 0 on boundary
/// f(x,y) =  cos(pi * (x - Bounds.Left) / Bounds.Width)) * cos(pi * (y - Bounds.Bottom) / Bounds.Height))
/// </summary>
class HelmholtzEquationWithSourceFEM : public FemProblem2dBase
{
private:
    Geometry::Rectangle m_bounds;
    float m_k;

public:
    HelmholtzEquationWithSourceFEM(const Geometry::Rectangle& bounds, const Geometry::Mesh2D& mesh, float k);

    float SourceFunction(Geometry::Vertex2F vertex) const;
    float AnalyticSolutionFunction(Geometry::Vertex2F position) const;
};
