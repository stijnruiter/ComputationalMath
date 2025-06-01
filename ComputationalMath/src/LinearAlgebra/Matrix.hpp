#pragma once
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

#include "VectorBase.hpp"

// #define SIMD_ACCELERATION

namespace LinearAlgebra
{
    template <typename T>
    class Matrix
    {
    public:
        Matrix();
        Matrix(size_t rowCount, size_t columnCount);
        Matrix(size_t rowCount, size_t columnCount, std::span<T> data);
        Matrix(size_t rowCount, size_t columnCount, const std::vector<T>& data);
        Matrix(const Matrix& mat);
        Matrix(const std::initializer_list<RowVector<T>>& values);

        T GetValue(size_t row, size_t column) const;
        void SetValue(size_t row, size_t column, const T& value);

        RowVector<T> GetRow(size_t row) const;
        ColumnVector<T> GetColumn(size_t column) const;

        T* Data();
        const T* Data() const;

        size_t GetRowCount() const;
        size_t GetColumnCount() const;

        bool ElementwiseEquals(const Matrix& mat) const;
        bool ElementwiseCompare(const Matrix& mat, float epsilon) const;

        void SwapRows(size_t row1, size_t row2);
        void Fill(const T& value);

        Matrix Transposed() const;

        static T Determinant(const T& m11, const T& m12,
                             const T& m21, const T& m22);

        static T Determinant(const T& m11, const T& m12, const T& m13,
                             const T& m21, const T& m22, const T& m23,
                             const T& m31, const T& m32, const T& m33);

    public:
        T& operator()(size_t row, size_t column);
        const T& operator()(size_t row, size_t column) const;
        Matrix operator+(const Matrix& mat) const;
        Matrix operator-(const Matrix& mat) const;

        Matrix operator*(const Matrix& mat) const;
        ColumnVector<T> operator*(const ColumnVector<T>& vector) const;
        Matrix operator*(const T& scalar) const;

    private:
        void ThrowIfOutOfRange(size_t row, size_t column) const;
        void ThrowIfRowOutOfRange(size_t row) const;
        void ThrowIfColumnOutOfRange(size_t column) const;
        void AssertNoOverflow() const;

        std::span<T> AsSpan();
        std::span<T> AsSpan() const;

    private:
        size_t m_length;
        size_t m_rowCount;
        size_t m_columnCount;

        std::shared_ptr<T[]> m_storage;
    };

    template <typename T>
    Matrix<T>::Matrix()
        : m_length(0), m_rowCount(0), m_columnCount(0)
    {
        m_storage.reset();
    }

    template <typename T>
    Matrix<T>::Matrix(size_t rowCount, size_t columnCount)
        : m_length(rowCount * columnCount), m_rowCount(rowCount), m_columnCount(columnCount)
    {
        AssertNoOverflow();
        m_storage.reset(new T[m_length]);
    }

    template <typename T>
    Matrix<T>::Matrix(size_t rowCount, size_t columnCount, std::span<T> data)
        : Matrix(rowCount, columnCount)
    {
        if (rowCount * columnCount != data.size())
            throw std::out_of_range("Data length different then row x column");

        T* destination = m_storage.get();
        std::copy(data.begin(), data.end(), destination);
    }

    template <typename T>
    Matrix<T>::Matrix(size_t rowCount, size_t columnCount, const std::vector<T>& data)
        : Matrix(rowCount, columnCount)
    {
        if (rowCount * columnCount != data.size())
            throw std::out_of_range("Data length different then row x column");

        T* destination = m_storage.get();
        std::copy(data.begin(), data.end(), destination);
    }

    template <typename T>
    Matrix<T>::Matrix(const Matrix& mat)
        : Matrix(mat.m_rowCount, mat.m_columnCount)
    {
        const T* source = mat.Data();
        T* destination = Data();
        std::copy(source, source + m_length, destination);
    }

    template <typename T>
    Matrix<T>::Matrix(const std::initializer_list<RowVector<T>>& values)
    {
        if (values.size() == 0)
        {
            m_columnCount = 0;
            m_rowCount = 0;
            m_length = 0;
            m_storage.reset();
            return;
        }

        m_rowCount = values.size();
        m_columnCount = values.begin()->GetLength();
        m_length = m_rowCount * m_columnCount;
        m_storage.reset(new T[m_length]);
        T* matrixData = m_storage.get();
        for (const RowVector<T>& row : values)
        {
            if (m_columnCount != row.GetLength())
                throw std::invalid_argument("Not all rows have identical lengths");
            const T* rowData = row.Data();
            std::copy(rowData, rowData + m_columnCount, matrixData);
            matrixData += m_columnCount;
        }
    }

    template <typename T>
    T Matrix<T>::GetValue(const size_t row, const size_t column) const
    {
        ThrowIfOutOfRange(row, column);
        return m_storage.get()[row * m_columnCount + column];
    }

    template <typename T>
    void Matrix<T>::SetValue(const size_t row, const size_t column, const T& value)
    {
        ThrowIfOutOfRange(row, column);
        m_storage.get()[row * m_columnCount + column] = value;
    }

    template <typename T>
    RowVector<T> Matrix<T>::GetRow(const size_t row) const
    {
        // TODO: implement view to avoid copies
        ThrowIfRowOutOfRange(row);
        return RowVector<T>(AsSpan().subspan(row * m_columnCount, m_columnCount));
    }

    template <typename T>
    ColumnVector<T> Matrix<T>::GetColumn(const size_t column) const
    {
        // TODO: implement view to avoid copies
        ThrowIfColumnOutOfRange(column);
        ColumnVector<T> result(m_rowCount);
        T* start = m_storage.get() + column;
        for (size_t i = 0; i < m_rowCount; i++)
        {
            result[i] = start[i * m_columnCount];
        }
        return result;
    }

    template <typename T>
    T* Matrix<T>::Data()
    {
        return m_storage.get();
    }

    template <typename T>
    const T* Matrix<T>::Data() const
    {
        return m_storage.get();
    }

    template <typename T>
    size_t Matrix<T>::GetRowCount() const
    {
        return m_rowCount;
    }

    template <typename T>
    size_t Matrix<T>::GetColumnCount() const
    {
        return m_columnCount;
    }

    template <typename T>
    bool Matrix<T>::ElementwiseEquals(const Matrix& mat) const
    {
        T* lhs = m_storage.get();
        T* rhs = mat.m_storage.get();
        return std::equal(lhs, lhs + m_length, rhs);
    }

    template <typename T>
    bool Matrix<T>::ElementwiseCompare(const Matrix& mat, float epsilon) const
    {
        T* lhs = m_storage.get();
        T* rhs = mat.m_storage.get();
        return std::equal(lhs, lhs + m_length, rhs, [epsilon](T& left, T& right)
                          { return std::abs(left - right) < epsilon; });
    }

    template <typename T>
    void Matrix<T>::SwapRows(const size_t row1, const size_t row2)
    {
        ThrowIfRowOutOfRange(row1);
        ThrowIfRowOutOfRange(row2);

        T* data = m_storage.get();
        size_t row1Start = row1 * m_columnCount;
        size_t row1End = row1Start + m_columnCount;
        size_t row2Start = row2 * m_columnCount;
        std::swap_ranges(data + row1Start, data + row1End, data + row2Start);
    }

    template <typename T>
    void Matrix<T>::Fill(const T& value)
    {
        T* destination = m_storage.get();
        std::fill(destination, destination + m_length, value);
    }

    template <typename T>
    Matrix<T> Matrix<T>::Transposed() const
    {
        Matrix transposedMat(m_columnCount, m_rowCount);
        const T* src = Data();
        T* dst = transposedMat.Data();

        constexpr size_t block = 32; // For cache locality
        for (size_t i = 0; i < m_rowCount; i += block)
        {
            for (size_t j = 0; j < m_columnCount; ++j)
            {
                for (size_t k = 0; k < block && i + k < m_rowCount; ++k)
                {
                    dst[j * m_rowCount + i + k] = src[(i + k) * m_columnCount + j];
                }
            }
        }
        return transposedMat;
    }

    template <typename T>
    T Matrix<T>::Determinant(const T& m11, const T& m12,
                             const T& m21, const T& m22)
    {
        return m11 * m22 - m21 * m12;
    }

    template <typename T>
    T Matrix<T>::Determinant(const T& m11, const T& m12, const T& m13,
                             const T& m21, const T& m22, const T& m23,
                             const T& m31, const T& m32, const T& m33)
    {
        return m11 * Determinant(m22, m23, m32, m33) - m12 * Determinant(m21, m23, m31, m33) + m13 * Determinant(m21, m22, m31, m32);
    }

    template <typename T>
    T& Matrix<T>::operator()(const size_t row, const size_t column)
    {
        return m_storage.get()[row * m_columnCount + column];
    }

    template <typename T>
    const T& Matrix<T>::operator()(const size_t row, const size_t column) const
    {
        return m_storage.get()[row * m_columnCount + column];
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& out, const Matrix<T>& e)
    {
        out << "Mat" << e.GetRowCount() << "x" << e.GetColumnCount();
        if (e.GetColumnCount() == 0 || e.GetRowCount() == 0)
            return out << "[]";

        out << std::endl
            << '[';

        for (size_t i = 0; i < e.GetRowCount(); i++)
        {
            if (i > 0)
            {
                out << std::endl;
            }
            out << '[';
            for (size_t j = 0; j < e.GetColumnCount(); j++)
            {
                out << (j == 0 ? "" : ", ") << e(i, j);
            }
            out << ']';
        }
        return out << ']';
    }

#ifdef SIMD_ACCELERATION
#include "SimdOps.h"
    template <>
    inline Matrix<int> Matrix<int>::operator+(const Matrix<int>& mat) const
    {
        if (m_columnCount != mat.m_columnCount || m_rowCount != mat.m_rowCount)
            throw std::invalid_argument("Dimensions mismatch");

        // Note, this operation is very simple, thus almost no time difference
        Matrix<int> result(m_rowCount, m_columnCount);
        LinearAlgebra::SimdOps::Sum(m_storage.get(), mat.m_storage.get(), m_length, result.m_storage.get());
        return result;
    }
#endif

    template <typename T>
    Matrix<T> Matrix<T>::operator+(const Matrix& mat) const
    {
        if (m_columnCount != mat.m_columnCount || m_rowCount != mat.m_rowCount)
            throw std::invalid_argument("Dimensions mismatch");

        T* lhs = m_storage.get();
        T* rhs = mat.m_storage.get();
        Matrix sum(m_rowCount, m_columnCount);
        T* sumPointer = sum.m_storage.get();
        std::transform(lhs, lhs + m_length, rhs, sumPointer, [](T& left, T& right)
                       { return left + right; });
        return sum;
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator-(const Matrix& mat) const
    {
        if (m_columnCount != mat.m_columnCount || m_rowCount != mat.m_rowCount)
            throw std::invalid_argument("Dimensions mismatch");

        // TODO: SIMD
        T* lhs = m_storage.get();
        T* rhs = mat.m_storage.get();

        Matrix subtract(m_rowCount, m_columnCount);
        T* subtractPointer = subtract.m_storage.get();
        std::transform(lhs, lhs + m_length, rhs, subtractPointer, [](T& left, T& right)
                       { return left - right; });
        return subtract;
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator*(const Matrix& mat) const
    {
        if (m_columnCount != mat.m_rowCount)
            throw std::invalid_argument("Matrix mismatch");

        // TODO: SIMD
        Matrix product(m_rowCount, mat.m_columnCount);
        for (size_t i = 0; i < m_rowCount; i++)
        {
            for (size_t j = 0; j < mat.m_columnCount; j++)
            {
                T dotProduct = 0;
                for (size_t k = 0; k < m_columnCount; k++)
                {
                    dotProduct += GetValue(i, k) * mat.GetValue(k, j);
                }
                product.SetValue(i, j, dotProduct);
            }
        }
        return product;
    }

    template <typename T>
    RowVector<T> operator*(const RowVector<T>& vector, const Matrix<T>& matrix)
    {
        if (vector.GetLength() != matrix.GetRowCount())
            throw std::invalid_argument("Row Matrix multiplication mismatch");

        RowVector<T> result(matrix.GetColumnCount());
        for (size_t i = 0; i < matrix.GetColumnCount(); i++)
        {
            result[i] = 0;
            for (size_t k = 0; k < matrix.GetRowCount(); k++)
            {
                result[i] += vector.GetValue(k) * matrix(k, i);
            }
        }
        return result;
    }

    template <typename T>
    ColumnVector<T> Matrix<T>::operator*(const ColumnVector<T>& vector) const
    {
        if (m_columnCount != vector.GetLength())
            throw std::invalid_argument("Matrix Column multiplication mismatch");

        ColumnVector<T> result(m_rowCount);
        for (size_t i = 0; i < m_rowCount; i++)
        {
            result[i] = 0;
            for (size_t k = 0; k < m_columnCount; k++)
            {
                result[i] += this->GetValue(i, k) * vector.GetValue(k);
            }
        }
        return result;
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator*(const T& scalar) const
    {
        Matrix result(m_rowCount, m_columnCount);
        T* source = m_storage.get();
        T* destination = result.m_storage.get();
        std::transform(source, source + m_length, destination, [scalar](T& sourceElement)
                       { return scalar * sourceElement; });
        return result;
    }

    template <typename T>
    Matrix<T> operator*(const T& scalar, const Matrix<T>& mat)
    {
        return mat * scalar;
    }

    template <typename T>
    void Matrix<T>::ThrowIfOutOfRange(const size_t row, const size_t column) const
    {
        if (row >= m_rowCount || column >= m_columnCount)
            throw std::out_of_range("Index out of range");
    }

    template <typename T>
    void Matrix<T>::ThrowIfRowOutOfRange(const size_t row) const
    {
        if (row >= m_rowCount)
            throw std::out_of_range("Row out of range");
    }

    template <typename T>
    void Matrix<T>::ThrowIfColumnOutOfRange(const size_t column) const
    {
        if (column >= m_columnCount)
            throw std::out_of_range("Column out of range");
    }

    template <typename T>
    void Matrix<T>::AssertNoOverflow() const
    {
        if (m_columnCount != 0 && m_length / m_columnCount != m_rowCount)
            throw std::overflow_error("NxM count size overflow");
    }

    template <typename T>
    std::span<T> Matrix<T>::AsSpan()
    {
        return std::span<T>{m_storage.get(), m_length};
    }

    template <typename T>
    std::span<T> Matrix<T>::AsSpan() const
    {
        return std::span<T>{m_storage.get(), m_length};
    }
}