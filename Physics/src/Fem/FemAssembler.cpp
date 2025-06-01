#include "FemAssembler.hpp"
#include <unordered_set>

namespace FemAssembler
{
    using namespace LinearAlgebra;

    Matrix<float> InitializeMatrix(const Geometry::Mesh2D& mesh)
    {
        Matrix<float> result(mesh.Vertices.size(), mesh.Vertices.size());
        result.Fill(0);
        return result;
    }

    ColumnVector<float> InitializeVector(const Geometry::Mesh2D& mesh)
    {
        ColumnVector<float> result(mesh.Vertices.size());
        result.Fill(0);
        return result;
    }

    ColumnVector<float> InitializeVector(const Geometry::Mesh2D& mesh, const VertexValueFunc& value)
    {
        ColumnVector<float> result(mesh.Vertices.size());
        std::transform(mesh.Vertices.begin(), mesh.Vertices.end(), result.begin(), value);
        return result;
    }

    void Add_Matrix_NablaA_NablaV(const Geometry::Mesh2D& mesh, Matrix<float>& matrix, const float scalar)
    {
        for (const auto& element : mesh.Interior)
        {
            const Geometry::Vertex2F vertex0 = mesh.Vertices[element.I];
            const Geometry::Vertex2F vertex1 = mesh.Vertices[element.J];
            const Geometry::Vertex2F vertex2 = mesh.Vertices[element.K];

            Matrix<float> jacobian = Jacobian(vertex0, vertex1, vertex2);
            const float detJ = Matrix<float>::Determinant(jacobian(0, 0), jacobian(0, 1), jacobian(1, 0), jacobian(1, 1));
            Matrix<float> invJT = Factorization::InverseMatrix(jacobian, 1e-5f).Transposed();

            ColumnVector<float> nablaPhi0 = invJT * ColumnVector<float>({-1, -1});
            ColumnVector<float> nablaPhi1 = invJT * ColumnVector<float>({1, 0});
            ColumnVector<float> nablaPhi2 = invJT * ColumnVector<float>({0, 1});

            matrix(element.I, element.I) += scalar * 0.5f * detJ * nablaPhi0.Transposed() * nablaPhi0;
            matrix(element.J, element.I) += scalar * 0.5f * detJ * nablaPhi1.Transposed() * nablaPhi0;
            matrix(element.K, element.I) += scalar * 0.5f * detJ * nablaPhi2.Transposed() * nablaPhi0;
            matrix(element.I, element.J) += scalar * 0.5f * detJ * nablaPhi0.Transposed() * nablaPhi1;
            matrix(element.J, element.J) += scalar * 0.5f * detJ * nablaPhi1.Transposed() * nablaPhi1;
            matrix(element.K, element.J) += scalar * 0.5f * detJ * nablaPhi2.Transposed() * nablaPhi1;
            matrix(element.I, element.K) += scalar * 0.5f * detJ * nablaPhi0.Transposed() * nablaPhi2;
            matrix(element.J, element.K) += scalar * 0.5f * detJ * nablaPhi1.Transposed() * nablaPhi2;
            matrix(element.K, element.K) += scalar * 0.5f * detJ * nablaPhi2.Transposed() * nablaPhi2;
        }
    }

    void Add_Matrix_U_V(const Geometry::Mesh2D& mesh, Matrix<float>& matrix, const float scalar)
    {
        for (const auto& element : mesh.Interior)
        {
            const Geometry::Vertex2F vertex0 = mesh.Vertices[element.I];
            const Geometry::Vertex2F vertex1 = mesh.Vertices[element.J];
            const Geometry::Vertex2F vertex2 = mesh.Vertices[element.K];

            Matrix<float> jacobian = Jacobian(vertex0, vertex1, vertex2);
            const float detJ = Matrix<float>::Determinant(jacobian(0, 0), jacobian(0, 1), jacobian(1, 0), jacobian(1, 1));

            matrix(element.I, element.I) += scalar * detJ / 12;
            matrix(element.J, element.I) += scalar * detJ / 24;
            matrix(element.K, element.I) += scalar * detJ / 24;
            matrix(element.I, element.J) += scalar * detJ / 24;
            matrix(element.J, element.J) += scalar * detJ / 12;
            matrix(element.K, element.J) += scalar * detJ / 24;
            matrix(element.I, element.K) += scalar * detJ / 24;
            matrix(element.J, element.K) += scalar * detJ / 24;
            matrix(element.K, element.K) += scalar * detJ / 12;
        }
    }

    void Add_Vector_U_F(const Geometry::Mesh2D& mesh, ColumnVector<float>& column, const std::function<float(Geometry::Vertex2F)>& sourceF)
    {
        for (const auto& element : mesh.Interior)
        {
            const Geometry::Vertex2F vertex0 = mesh.Vertices[element.I];
            const Geometry::Vertex2F vertex1 = mesh.Vertices[element.J];
            const Geometry::Vertex2F vertex2 = mesh.Vertices[element.K];

            Matrix<float> jacobian = Jacobian(vertex0, vertex1, vertex2);
            const float detJ = Matrix<float>::Determinant(jacobian(0, 0), jacobian(0, 1), jacobian(1, 0), jacobian(1, 1)); 

            const float f0 = sourceF(vertex0) / 24;
            const float f1 = sourceF(vertex1) / 24;
            const float f2 = sourceF(vertex2) / 24;

            column[element.I] += detJ * (2 * f0 + f1 + f2);
            column[element.J] += detJ * (f0 + 2 * f1 + f2);
            column[element.K] += detJ * (f0 + f1 + 2 * f2);
        }
    }

    void AddNaturalBoundaryConditions(const Geometry::Mesh2D& mesh, ColumnVector<float>& column, const std::function<float(Geometry::Vertex2F, Geometry::Vertex2F)>& constNaturalBoundaryFunc)
    {
        for (const auto& boundaryElement : mesh.Boundary)
        {
            const Geometry::Vertex2F vertex0 = mesh.Vertices[boundaryElement.I];
            const Geometry::Vertex2F vertex1 = mesh.Vertices[boundaryElement.J];
            const float length = vertex0.DistanceTo(vertex1);

            const float constNaturalBoundary = 0.5f * length * constNaturalBoundaryFunc(vertex0, vertex1);

            column[boundaryElement.I] += constNaturalBoundary;
            column[boundaryElement.J] += constNaturalBoundary;
        }
    }

    void ApplyEssentialBoundaryCondition(const Geometry::Mesh2D& mesh, Matrix<float>& matrix, ColumnVector<float>& column, const std::function<bool(Geometry::Vertex2F, float& output)>& essentialBoundaryFunc)
    {
        std::unordered_set<unsigned int> boundaryIndices;
        for (const auto& boundaryElement : mesh.Boundary)
        {
            boundaryIndices.insert(boundaryElement.I);
            boundaryIndices.insert(boundaryElement.J);
        }

        for (const unsigned int boundaryIndex : boundaryIndices)
        {
            const Geometry::Vertex2F vertex0 = mesh.Vertices[boundaryIndex];
            float value = 0;

            if (!essentialBoundaryFunc(vertex0, value))
                continue;

            for (size_t j = 0; j < matrix.GetColumnCount(); j++)
            {
                matrix(boundaryIndex, j) = 0.0f;
            }

            matrix(boundaryIndex, boundaryIndex) = 1.0f;
            column[boundaryIndex] = value;
        }
    }

    Matrix<float> Jacobian(const Geometry::Vertex2F vertex1, const Geometry::Vertex2F vertex2, const Geometry::Vertex2F vertex3)
    {
        return Matrix<float>({{vertex2.X - vertex1.X, vertex3.X - vertex1.X},
                              {vertex2.Y - vertex1.Y, vertex3.Y - vertex1.Y}});
    }
}