#pragma once

#include <Geometry/Structures/Mesh2D.hpp>
#include <LinearAlgebra/FactorizationLU.hpp>
#include <LinearAlgebra/Matrix.hpp>

#include <functional>
#include <unordered_set>

class FemProblem2dBase
{
private:
    Geometry::Mesh2D m_mesh;
    Matrix<float> m_matrix;
    ColumnVector<float> m_vector;

public:
    FemProblem2dBase(Geometry::Mesh2D mesh);

    const Geometry::Mesh2D& GetMesh() const { return m_mesh; }

    const Matrix<float>& MatrixA() const { return m_matrix; }

    const ColumnVector<float> VectorB() const { return m_vector; }

    ColumnVector<float> Solve() const;

private:
    static Matrix<float> Jacobian(Geometry::Vertex2F vertex1, Geometry::Vertex2F vertex2, Geometry::Vertex2F vertex3);

protected:
    void Add_Matrix_NablaA_NablaV(float scalar);

    void Add_Matrix_U_V(float scalar);

    void Add_Vector_U_F(std::function<float(Geometry::Vertex2F)> sourceF);

    void ApplyNaturalBoundaryConditions(std::function<float(Geometry::Vertex2F, Geometry::Vertex2F)> constNaturalBoundaryFunc);

    void ApplyEssentialBoundaryCondition(std::function<bool(Geometry::Vertex2F, float& output)> essentialBoundaryFunc);
};
