#pragma once

#include <algorithm>
#include <numeric>
#include "Matrix.h"

namespace LinearAlgebra
{
    namespace Factorization
    {
        size_t* IntRange(size_t max);
        
        template<typename T>
        struct IndexedExtremeValue { size_t Index; T Value; };
        
        template<typename T>
        struct FactorizationResult
        {
            Matrix<T> Factorization;
            int PermutationCount;
            size_t* Pivots;
        };
        
        template<typename T>
        IndexedExtremeValue<T> FindNextPivotRow(const Matrix<T>& matrix, size_t column)
        {
            IndexedExtremeValue<T> result;
            result.Index = -1;
            result.Value = 0;
            for(size_t i = column; i < matrix.GetRowCount(); i++)
            {
                T next = std::abs(matrix(i, column));
                if (next > result.Value)
                {
                    result.Value = next;
                    result.Index = i;
                }
            }
            return result;
        }
        
        template<typename T>
        FactorizationResult<T> PluFactorization(Matrix<T> A, T tolerance)
        {
            FactorizationResult<T> factorization { Matrix<T>(A), 0, IntRange(A.GetColumnCount()) };
        
            for (int i = 0; i < A.GetColumnCount(); i++)
            {
                IndexedExtremeValue<T> result = FindNextPivotRow(factorization.Factorization, i);
        
                if (result.Value <= tolerance || result.Index == -1) // No pivot column found in column i
                    throw std::invalid_argument("Degenerate matrix");
        
                if (result.Index != i)
                {
                    std::swap(factorization.Pivots[i], factorization.Pivots[result.Index]);
                    factorization.Factorization.SwapRows(i, result.Index);
                    factorization.PermutationCount++;
                }
        
                for (size_t j = i + 1; j < factorization.Factorization.GetRowCount(); j++)
                {
                    factorization.Factorization(j, i) /= factorization.Factorization(i, i);
                    for (size_t k = i + 1; k < factorization.Factorization.GetColumnCount(); k++)
                    {
                        factorization.Factorization(j, k) -= factorization.Factorization(j, i) * factorization.Factorization(i, k);
                    }
                };
            }
        
            return factorization;
        }
        
        template<typename T>
        Matrix<T> ExtractUpperMatrix(const Matrix<T>& matrix)
        {
            size_t rowCount = matrix.GetRowCount();
            size_t columnCount = matrix.GetColumnCount();
            const T* source = matrix.Data();
        
            Matrix<T> result(rowCount, columnCount);
            T* destination = result.Data();
            
            for (size_t i = 0; i < rowCount; i++)
            {
                std::fill(destination, destination + i, 0);
                std::copy(source + i, source + columnCount, destination + i);
                source += columnCount;
                destination += columnCount;
            }
        
            return result;
        }
        
        template<typename T>
        Matrix<T> ExtractLowerMatrix(const Matrix<T>& matrix)
        {
            size_t rowCount = matrix.GetRowCount();
            size_t columnCount = matrix.GetColumnCount();
        
            const T* source = matrix.Data();
        
            Matrix<T> result(rowCount, columnCount);
            T* destination = result.Data();
        
            for (size_t i = 0; i < rowCount; i++)
            {
                std::copy(source, source + i, destination);
                destination[i] = 1;
                std::fill(destination + i + 1, destination + columnCount, 0);
        
                source += columnCount;
                destination += columnCount;
            }
        
            return result;
        }
        
        template<typename T>
        T Determinant(Matrix<T> matrix, T tolerance)
        {
            if (matrix.GetColumnCount() != matrix.GetRowCount())
                throw std::invalid_argument("Cannot compute determinant of non-square matrix");
        
            FactorizationResult<T> results = PluFactorization(matrix, tolerance);
            return Determinant(results);
        }
        
        template<typename T>
        T Determinant(FactorizationResult<T> results)
        {
            if (results.Factorization.GetColumnCount() != results.Factorization.GetRowCount())
                throw std::invalid_argument("Cannot compute determinant of non-square matrix");
        
            T determinant = (results.PermutationCount % 2 == 0 ? 1 : -1);
        
            for (size_t i = 0; i < results.Factorization.GetRowCount(); i++)
            {
                determinant *= results.Factorization(i,i);
            }
        
            return determinant;
        }
    
        template<typename T>
        void ForwardSubstitutionInPlace(const Matrix<T>& matrix, ColumnVector<T>& rhs)
        {
            size_t columnCount = matrix.GetColumnCount();
            size_t rowCount = matrix.GetRowCount();
            if(columnCount != rhs.GetLength())
                throw std::invalid_argument("Matrix and Vector dimensions mismatch");
            if (columnCount != rowCount)
                throw std::invalid_argument("Non-square matrix");

            // const T* matrixData = matrix.Data();
            // T* rhsData = rhs.Data();

            for (size_t i = 0; i < columnCount; i++)
            {
                T sum = 0;
                for (int k = 0; k < i; k++)
                {
                    sum += matrix(i, k) * rhs[k];
                }
                rhs[i] -= sum;
                // rhsData[i] -= std::inner_product(matrixData, matrixData + i, rhsData, 0);
                // matrixData += columnCount;
            }
        }

        template<typename T>
        void ForwardSubstitutionInPlace(const Matrix<T>& matrix, Matrix<T>& rhs)
        {
            size_t columnCount = matrix.GetColumnCount();
            size_t rowCount = matrix.GetRowCount();
            if (columnCount != rowCount)
                throw std::invalid_argument("Non-square matrix");
            if (columnCount != rhs.GetColumnCount() || rowCount != rhs.GetRowCount())
                throw std::invalid_argument("Matrix Matrix mismatch") ;

            // const T* matrixData = matrix.Data();
            // T* rhsData = rhs.Data();

            for (size_t i = 0; i < rowCount; i++)
            {
                for (size_t j = 0; j < columnCount; j++)
                {
                    T sum = 0;
                    for (int k = 0; k < i; k++)
                    {
                        sum += matrix(i, k) * rhs(k, j);
                    }
                    rhs(i, j) -= sum;
                }
            }
        }

        template<typename T>
        void BackwardSubstitutionInPlace(const Matrix<T>& matrix, ColumnVector<T>& rhs)
        {
            size_t columnCount = matrix.GetColumnCount();
            size_t rowCount = matrix.GetRowCount();
            if(columnCount != rhs.GetLength())
                throw std::invalid_argument("Matrix and Vector dimensions mismatch");      
            if (columnCount != rowCount)
                throw std::invalid_argument("Non-square matrix");      
            

            // Sweeping backwards, starting at last row
            const T* matrixData = matrix.Data(); 
            T* rhsData = rhs.Data();

            for (size_t i = (rowCount - 1); i < rowCount; i--) // unsigned i overflow > rowCount
            {
                T sum = 0;
                for (size_t k = i + 1; k < rowCount; k++)
                {
                    sum += matrix(i, k) * rhs[k];
                }
                rhs[i] = (rhs[i] - sum) / matrix(i, i);
            }
        }

        template<typename T>
        void BackwardSubstitutionInPlace(const Matrix<T>& matrix, Matrix<T>& rhs)
        {
            size_t columnCount = matrix.GetColumnCount();
            size_t rowCount = matrix.GetRowCount();  
            if (columnCount != rowCount)
                throw std::invalid_argument("Non-square matrix");      
            if (columnCount != rhs.GetColumnCount() || rowCount != rhs.GetRowCount())
                throw std::invalid_argument("Matrix Matrix mismatch") ;
            

            // Sweeping backwards, starting at last row
            const T* matrixData = matrix.Data(); 
            T* rhsData = rhs.Data();

            for (size_t i = (rowCount - 1); i < rowCount; i--) // unsigned i overflow > rowCount
            {
                for (size_t j = 0; j < columnCount; j++)
                {
                    T sum = 0;
                    for (size_t k = i + 1; k < rowCount; k++)
                    {
                        sum += matrix(i, k) * rhs(k, j);
                    }
                    rhs(i, j) = (rhs(i, j) - sum) / matrix(i, i);
                }
            }
        }

        template<typename T>
        ColumnVector<T> LUSolve(const Matrix<T>& matrix, const ColumnVector<T>& rhs, T tolerance)
        {
            if (matrix.GetColumnCount() != matrix.GetRowCount())
                throw std::invalid_argument("Non-square matrix");
            if (matrix.GetColumnCount() != rhs.GetLength())
                throw std::invalid_argument("Matrix Column mismatch");
            
            // LU decomposition: P A = L U
            FactorizationResult<T> results = PluFactorization(matrix, tolerance);

            // Ax = b <=> PAx = Pb = LUx
            ColumnVector<T> Pb(rhs.GetLength());
            for (size_t i = 0; i < rhs.GetLength(); i++)
            {
                Pb[i] = rhs[results.Pivots[i]];
            }

            // Solve Ly=b
            ForwardSubstitutionInPlace(results.Factorization, Pb);

            // Solve Ux=y
            BackwardSubstitutionInPlace(results.Factorization, Pb);

            return Pb;
        }

        template<typename T>
        Matrix<T> LUSolve(const Matrix<T>& matrix, const Matrix<T>& rhs, T tolerance)
        {
            if (matrix.GetColumnCount() != matrix.GetRowCount())
                throw std::invalid_argument("Non-square matrix");
            if (matrix.GetColumnCount() != rhs.GetColumnCount() || matrix.GetRowCount() != rhs.GetRowCount())
                throw std::invalid_argument("Matrix Matrix mismatch") ;
            
            // LU decomposition: P A = L U
            FactorizationResult<T> results = PluFactorization(matrix, tolerance);

            // Ax = b <=> PAx = Pb = LUx
            Matrix<T> Pb(rhs.GetRowCount(), rhs.GetColumnCount());
            for (size_t i = 0; i < rhs.GetRowCount(); i++)
            {
                for (size_t j = 0; j < rhs.GetColumnCount(); j++)
                {
                    Pb(i, j) = rhs(results.Pivots[i], j);
                }
            }

            // Solve Ly=b
            ForwardSubstitutionInPlace(results.Factorization, Pb);

            // Solve Ux=y
            BackwardSubstitutionInPlace(results.Factorization, Pb);

            return Pb;
        }

        template<typename T>
        Matrix<T> Identity(size_t N)
        {
            Matrix<T> identity(N, N);
            T* data = identity.Data();
            std::fill(data, data + N * N, 0);
            for (size_t i = 0; i < N; i++)
            {
                identity(i, i) = 1;
            }
            return identity;
        }

        template<typename T>
        Matrix<float> InverseMatrix(const Matrix<float>& matrix, T tolerance)
        {
            if (matrix.GetColumnCount() != matrix.GetRowCount())
                throw std::invalid_argument("Non-square matrix");

            Matrix<float> identity = Identity<float>(matrix.GetColumnCount());
            return LUSolve(matrix, identity, tolerance);
        }
    }
}
