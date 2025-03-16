#pragma once

#include "FemProblem2DBase.h"
#include <Geometry/Structures/Rectangle.h>
#include "math.h"

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
    float SourceFunction(Geometry::Vertex2F vertex)
    {
        return (m_k + std::pow(M_PI / m_bounds.GetWidth(), 2) + std::pow(M_PI / m_bounds.GetHeight(), 2)) * AnalyticSolutionFunction(vertex);
    }

    HelmholtzEquationWithSourceFEM(const Geometry::Rectangle& bounds, const Geometry::Mesh2D& mesh, float k) 
        : FemProblem2dBase(mesh), m_bounds(bounds), m_k(k)
    {
        Add_Matrix_NablaA_NablaV(-1.0f);
        Add_Matrix_U_V(m_k);
        Add_Vector_U_F([this](Geometry::Vertex2F vertex) { return this->SourceFunction(vertex); });
    }

    float AnalyticSolutionFunction(Geometry::Vertex2F position)
    {
        float radX = M_PI * (position.X + m_bounds.Left) / m_bounds.GetWidth();
        float radY = M_PI * (position.Y + m_bounds.Bottom) / m_bounds.GetHeight();

        return std::cos(radX) * std::cos(radY);
    }

};
