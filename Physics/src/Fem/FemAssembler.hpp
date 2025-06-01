#pragma once

#include <Geometry/Structures/Mesh2D.hpp>
#include <LinearAlgebra/FactorizationLU.hpp>
#include <LinearAlgebra/Matrix.hpp>
#include <functional>

namespace FemAssembler
{
    typedef std::function<float(Geometry::Vertex2F)> VertexValueFunc;

    LinearAlgebra::Matrix<float> InitializeMatrix(const Geometry::Mesh2D& mesh);
    LinearAlgebra::ColumnVector<float> InitializeVector(const Geometry::Mesh2D& mesh);
    LinearAlgebra::ColumnVector<float> InitializeVector(const Geometry::Mesh2D& mesh, VertexValueFunc value);

    void Add_Matrix_NablaA_NablaV(const Geometry::Mesh2D& mesh, LinearAlgebra::Matrix<float>& matrix, float scalar);

    void Add_Matrix_U_V(const Geometry::Mesh2D& mesh, LinearAlgebra::Matrix<float>& matrix, float scalar);

    void Add_Vector_U_F(const Geometry::Mesh2D& mesh, LinearAlgebra::ColumnVector<float>& column, std::function<float(Geometry::Vertex2F)> sourceF);

    void AddNaturalBoundaryConditions(const Geometry::Mesh2D& mesh, LinearAlgebra::ColumnVector<float>& column, std::function<float(Geometry::Vertex2F, Geometry::Vertex2F)> constNaturalBoundaryFunc);

    void ApplyEssentialBoundaryCondition(const Geometry::Mesh2D& mesh, LinearAlgebra::Matrix<float>& matrix, LinearAlgebra::ColumnVector<float>& column, std::function<bool(Geometry::Vertex2F, float& output)> essentialBoundaryFunc);

    LinearAlgebra::Matrix<float> Jacobian(Geometry::Vertex2F vertex1, Geometry::Vertex2F vertex2, Geometry::Vertex2F vertex3);
};