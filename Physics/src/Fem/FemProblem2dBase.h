#pragma once

#include <Geometry/Structures/Mesh2D.h>
#include <LinearAlgebra/Matrix.h>
#include <LinearAlgebra/FactorizationLU.h>

#include <functional>
#include <unordered_set>

class FemProblem2dBase
{
private:
    Geometry::Mesh2D m_mesh;
    Matrix<float> m_matrix;
    ColumnVector<float> m_vector;

public:
    FemProblem2dBase(Geometry::Mesh2D mesh) : m_mesh(mesh), m_matrix(mesh.Vertices.size(), mesh.Vertices.size()), m_vector(mesh.Vertices.size())
    {
        m_matrix.Fill(0);
        m_vector.Fill(0);
    }

    const Geometry::Mesh2D& GetMesh() const { return m_mesh; }

    const Matrix<float>& MatrixA() const { return m_matrix; }

    const ColumnVector<float> VectorB() const { return m_vector; }

    // public ColumnVector<float> AnalyticSolution
    // {
    //     get
    //     {
    //         if (!HasAnalyticSolution)
    //             throw new Exception("This problem does not have an analytic solution.");

    //         if (_analyticSolution == null)
    //         {
    //             _analyticSolution = new ColumnVector<float>(Mesh.Vertices.Select(v => AnalyticSolutionFunction(v.Position)).ToArray());
    //         }

    //         return _analyticSolution;
    //     }
    // }

    // public abstract bool HasAnalyticSolution { get; }

    ColumnVector<float> Solve() const
    {
        return LinearAlgebra::Factorization::LUSolve(m_matrix, m_vector, 1e-5f);

        // m_matrix
        // _solution = MatrixA.Solve(VectorB);
        // Mesh.SetFemValues(_solution);
        // LogDifferences();
        // return _solution;
    }

    // private void LogDifferences()
    // {
    //     string output = (GetType().Name + " finished") + Environment.NewLine;
    //     if (Solution is not null && HasAnalyticSolution && AnalyticSolution is not null)
    //     {
    //         output += ($"|u-u_h|_1 = {(Solution - AnalyticSolution).Norm1()}") + Environment.NewLine;
    //         output += ($"|u-u_h|_2 = {(Solution - AnalyticSolution).Norm2()}") + Environment.NewLine;
    //         output += ($"|u-u_h|_Inf = {(Solution - AnalyticSolution).NormInf()}") + Environment.NewLine;
    //     }
    //     Debug.WriteLine(output);
    // }

    // protected abstract float AnalyticSolutionFunction(Vertex3 position);

private:
    static Matrix<float> Jacobian(Geometry::Vertex2F vertex1, Geometry::Vertex2F vertex2, Geometry::Vertex2F vertex3)
    {
        return Matrix<float>(2, 2, new float[4]{
            vertex2.X - vertex1.X, vertex3.X - vertex1.X,
            vertex2.Y - vertex1.Y, vertex3.Y - vertex1.Y
        });
    }

protected:
    void Add_Matrix_NablaA_NablaV(float scalar)
    {
        for (const auto& element : m_mesh.Interior)
        {
            const Geometry::Vertex2F vertex0 = m_mesh.Vertices[element.I];
            const Geometry::Vertex2F vertex1 = m_mesh.Vertices[element.J];
            const Geometry::Vertex2F vertex2 = m_mesh.Vertices[element.K];

            Matrix<float> jacobian = Jacobian(vertex0, vertex1, vertex2);
            float detJ = jacobian.Determinant(jacobian(0,0), jacobian(0, 1), jacobian(1,0), jacobian(1,1)); // TODO: fix
            Matrix<float> invJT = LinearAlgebra::Factorization::InverseMatrix(jacobian, 1e-5f).Transposed();

            ColumnVector<float> nablaPhi0 = invJT * ColumnVector<float>(2, new float[2]{-1, -1});
            ColumnVector<float> nablaPhi1 = invJT * ColumnVector<float>(2, new float[2]{1, 0});
            ColumnVector<float> nablaPhi2 = invJT * ColumnVector<float>(2, new float[2]{0, 1});
            auto var1 = 0.5f * detJ * nablaPhi0.Transposed() * nablaPhi0;
            auto var2 = 0.5f * detJ * nablaPhi1.Transposed() * nablaPhi0;
            auto var3 = 0.5f * detJ * nablaPhi2.Transposed() * nablaPhi0;
            auto var4 = 0.5f * detJ * nablaPhi0.Transposed() * nablaPhi1;
            auto var5 = 0.5f * detJ * nablaPhi1.Transposed() * nablaPhi1;
            auto var6 = 0.5f * detJ * nablaPhi2.Transposed() * nablaPhi1;
            auto var7 = 0.5f * detJ * nablaPhi0.Transposed() * nablaPhi2;
            auto var8 = 0.5f * detJ * nablaPhi1.Transposed() * nablaPhi2;
            auto var9 = 0.5f * detJ * nablaPhi2.Transposed() * nablaPhi2;
            m_matrix(element.I, element.I) += var1;
            m_matrix(element.J, element.I) += var2;
            m_matrix(element.K, element.I) += var3;
            m_matrix(element.I, element.J) += var4;
            m_matrix(element.J, element.J) += var5;
            m_matrix(element.K, element.J) += var6;
            m_matrix(element.I, element.K) += var7;
            m_matrix(element.J, element.K) += var8;
            m_matrix(element.K, element.K) += var9;
        }
    }

    void Add_Matrix_U_V(float scalar)
    {
        for (const auto& element : m_mesh.Interior)
        {
            const Geometry::Vertex2F vertex0 = m_mesh.Vertices[element.I];
            const Geometry::Vertex2F vertex1 = m_mesh.Vertices[element.J];
            const Geometry::Vertex2F vertex2 = m_mesh.Vertices[element.K];

            Matrix<float> jacobian = Jacobian(vertex0, vertex1, vertex2);
            float detJ = jacobian.Determinant(jacobian(0,0), jacobian(0, 1), jacobian(1,0), jacobian(1,1)); // TODO: fix

            m_matrix(element.I, element.I) += scalar * detJ / 12;
            m_matrix(element.J, element.I) += scalar * detJ / 24;
            m_matrix(element.K, element.I) += scalar * detJ / 24;
            m_matrix(element.I, element.J) += scalar * detJ / 24;
            m_matrix(element.J, element.J) += scalar * detJ / 12;
            m_matrix(element.K, element.J) += scalar * detJ / 24;
            m_matrix(element.I, element.K) += scalar * detJ / 24;
            m_matrix(element.J, element.K) += scalar * detJ / 24;
            m_matrix(element.K, element.K) += scalar * detJ / 12;
        }
    }

    void Add_Vector_U_F(std::function<float(Geometry::Vertex2F)> sourceF)
    {
        for (const auto& element : m_mesh.Interior)
        {
            const Geometry::Vertex2F vertex0 = m_mesh.Vertices[element.I];
            const Geometry::Vertex2F vertex1 = m_mesh.Vertices[element.J];
            const Geometry::Vertex2F vertex2 = m_mesh.Vertices[element.K];

            Matrix<float> jacobian = Jacobian(vertex0, vertex1, vertex2);
            float detJ = jacobian.Determinant(jacobian(0,0), jacobian(0, 1), jacobian(1,0), jacobian(1,1)); // TODO: fix

            float f0 = sourceF(vertex0) / 24;
            float f1 = sourceF(vertex1) / 24;
            float f2 = sourceF(vertex2) / 24;

            m_vector[element.I] += detJ * (2 * f0 + f1 + f2);
            m_vector[element.J] += detJ * (f0 + 2 * f1 + f2);
            m_vector[element.K] += detJ * (f0 + f1 + 2 * f2);
        }
    }

    void ApplyNaturalBoundaryConditions(std::function<float(Geometry::Vertex2F, Geometry::Vertex2F)> constNaturalBoundaryFunc)
    {
        for(const auto& boundaryElement : m_mesh.Boundary)
        {
            const Geometry::Vertex2F vertex0 = m_mesh.Vertices[boundaryElement.I];
            const Geometry::Vertex2F vertex1 = m_mesh.Vertices[boundaryElement.J];
            float length = vertex0.DistanceTo(vertex1);

            float constNaturalBoundary = 0.5f * length * constNaturalBoundaryFunc(vertex0, vertex1);

            m_vector[boundaryElement.I] += constNaturalBoundary;
            m_vector[boundaryElement.J] += constNaturalBoundary;
        }
    }

    void ApplyEssentialBoundaryCondition(std::function<bool(Geometry::Vertex2F, float& output)> essentialBoundaryFunc)
    {
        std::unordered_set<unsigned int> boundaryIndices;
        for(const auto& boundaryElement : m_mesh.Boundary)
        {
            boundaryIndices.insert(boundaryElement.I);
            boundaryIndices.insert(boundaryElement.J);
        }

        // foreach (var boundaryIndex in Mesh.BoundaryElements.SelectMany(line => new[] { line.I, line.J }).Distinct())
        for(unsigned int boundaryIndex : boundaryIndices)
        {
            const Geometry::Vertex2F vertex0 = m_mesh.Vertices[boundaryIndex];
            float value = 0;

            if (!essentialBoundaryFunc(vertex0, value))
                continue;

            for (size_t j = 0; j < m_matrix.GetColumnCount(); j++)
            {
                m_matrix(boundaryIndex, j) = 0.0f;
            }

            m_matrix(boundaryIndex, boundaryIndex) = 1.0f;
            m_vector[boundaryIndex] = value;
        }
    }


    // private ColumnVector<float>? _analyticSolution;

    // private ColumnVector<float>? _solution;
};
