#pragma once
#include "FemProblem2DBase.h"
#include <Geometry/Structures/Rectangle.h>
#include "math.h"
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
    LaplaceFem(const Geometry::Rectangle& bounds, const Geometry::Mesh2D& mesh) : FemProblem2dBase(mesh)
    {
        m_bounds = bounds;
        Add_Matrix_NablaA_NablaV(1.0f);
    
        ApplyNaturalBoundaryConditions([this](Geometry::Vertex2F vertex1, Geometry::Vertex2F vertex2) { 
            return this->NaturalBoundaryCondition(vertex1, vertex2); 
        });
        ApplyEssentialBoundaryCondition([this](Geometry::Vertex2F vertex, float& value) { 
            return this->EssentialBoundaryCondition(vertex, value); 
        });
    }

    float NaturalBoundaryCondition(Geometry::Vertex2F vertex1, Geometry::Vertex2F vertex2)
    {
        // dU/dn = \nabla Y * n = (0, 1) * n
        if (vertex1.Y == vertex2.Y && vertex1.Y == m_bounds.Bottom) // n = (0, -1)
            return -1.0f;

        if (vertex1.Y == vertex2.Y && vertex1.Y == m_bounds.Top) // n = (0, 1)
            return 1.0f;

        return 0.0f; // n = (1, 0) | (-1, 0)
    }

    bool EssentialBoundaryCondition(Geometry::Vertex2F vertex1, float& result)
    {
        result = vertex1.Y;
        return (vertex1.X == m_bounds.Left || vertex1.X == m_bounds.Right);
    }

    float AnalyticSolutionFunction(Geometry::Vertex2F position)
    {
        return position.Y;
    }
};
