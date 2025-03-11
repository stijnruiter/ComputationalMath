#pragma once
#include <memory>
#include <algorithm>
#include <stdexcept>

#define SIMD_ACCELERATION

template<typename T>
class Matrix
{
public:
	Matrix();
	Matrix(size_t rowCount, size_t columnCount);
	Matrix(size_t rowCount, size_t columnCount, const T* data);

	T& GetValue(size_t row, size_t column) const;
	void SetValue(size_t row, size_t column, const T& value);

	size_t GetRowCount() const;
	size_t GetColumnCount() const;

	bool ElementwiseEquals(const Matrix<T>& mat) const;
	bool ElementwiseCompare(const Matrix<T>& mat, float epsilon) const;

	T& operator()(size_t row, size_t column) const;
	Matrix<T> operator+(const Matrix<T>& mat) const;
	Matrix<T> operator-(const Matrix<T>& mat) const;

	Matrix<T> operator*(const Matrix<T>& mat) const;

private:
	void ThrowIfOutOfRange(size_t row, size_t column) const;
	void ThrowIfRowOutOfRange(size_t row) const;
	void ThrowIfColumnOutOfRange(size_t column) const;
	void AssertNoOverflow() const;

private:
	size_t m_length;
	size_t m_rowCount;
	size_t m_columnCount;

	std::shared_ptr<T[]> m_storage;
};

template<typename T>
inline Matrix<T>::Matrix() : m_rowCount(0), m_columnCount(0), m_length(0)
{
	m_storage.reset();
}

template<typename T>
inline Matrix<T>::Matrix(size_t rowCount, size_t columnCount) 
	:m_rowCount(rowCount), m_columnCount(columnCount), m_length(rowCount * columnCount)
{
	AssertNoOverflow();
	m_storage.reset(new T[m_length]);
}

template<typename T>
inline Matrix<T>::Matrix(size_t rowCount, size_t columnCount, const T* data)
	: Matrix<T>(rowCount, columnCount)
{
	T* destination = m_storage.get();
	std::copy(data, data + m_length, destination);
}

template<typename T>
inline T& Matrix<T>::GetValue(size_t row, size_t column) const
{
	ThrowIfOutOfRange(row, column);
	return m_storage.get()[row * m_columnCount + column];
}

template<typename T>
inline void Matrix<T>::SetValue(size_t row, size_t column, const T& value)
{
	ThrowIfOutOfRange(row, column);
	m_storage.get()[row * m_columnCount + column] = value;
}

template<typename T>
inline size_t Matrix<T>::GetRowCount() const
{
	return m_rowCount;
}

template<typename T>
inline size_t Matrix<T>::GetColumnCount() const
{
	return m_columnCount;
}

template<typename T>
inline bool Matrix<T>::ElementwiseEquals(const Matrix<T>& mat) const
{
	T* lhs = m_storage.get();
	T* rhs = mat.m_storage.get();
	return std::equal(lhs, lhs + m_length, rhs);
}

template<typename T>
inline bool Matrix<T>::ElementwiseCompare(const Matrix<T>& mat, float epsilon) const
{
	T* lhs = m_storage.get();
	T* rhs = mat.m_storage.get();
	return std::equal(lhs, lhs + m_length, rhs, [epsilon](T& left, T& right) { return std::abs(left - right) < epsilon; });
}

template<typename T>
inline T& Matrix<T>::operator()(size_t row, size_t column) const
{
	return GetValue(row, column);
}

#ifdef SIMD_ACCELERATION
#include "SimdOps.h"
template <>
inline Matrix<int> Matrix<int>::operator+(const Matrix<int>& mat) const
{
	if (m_columnCount != mat.m_columnCount || m_rowCount != mat.m_rowCount)
		throw std::invalid_argument("Dimensions mismatch");
	
	Matrix<int> result(m_rowCount, m_columnCount);
	LinearAlgebra::SimdOps::Sum(m_storage.get(), mat.m_storage.get(), m_length, result.m_storage.get());
	return result;
}
#endif

template<typename T>
inline Matrix<T> Matrix<T>::operator+(const Matrix<T>& mat) const
{
	if (m_columnCount != mat.m_columnCount || m_rowCount != mat.m_rowCount)
		throw std::invalid_argument("Dimensions mismatch");

	T* lhs = m_storage.get();
	T* rhs = mat.m_storage.get();
	Matrix<T> sum(m_rowCount, m_columnCount);
	T* sumPointer = sum.m_storage.get();
	std::transform(lhs, lhs + m_length, rhs, sumPointer, [](T& left, T& right) {return left + right; });
	return sum;
}

template<typename T>
inline Matrix<T> Matrix<T>::operator-(const Matrix<T>& mat) const
{
	if (m_columnCount != mat.m_columnCount || m_rowCount != mat.m_rowCount)
		throw std::invalid_argument("Dimensions mismatch");

	// TODO: SIMD
	T* lhs = m_storage.get();
	T* rhs = mat.m_storage.get();

	Matrix<T> subtract(m_rowCount, m_columnCount);
	T* subtractPointer = subtract.m_storage.get();
	std::transform(lhs, lhs + m_length, rhs, subtractPointer, [](T& left, T& right) {return left - right; });
	return subtract;
}

template<typename T>
inline Matrix<T> Matrix<T>::operator*(const Matrix<T>& mat) const
{
	if (m_columnCount != mat.m_rowCount)
		throw std::invalid_argument("Matrix mismatch");

	// TODO: SIMD
	Matrix<T> product(m_rowCount, mat.m_columnCount);
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

template<typename T>
inline void Matrix<T>::ThrowIfOutOfRange(size_t row, size_t column) const
{
	if (row >= m_rowCount || column >= m_columnCount)
		throw std::out_of_range("Index out of range");
}

template<typename T>
inline void Matrix<T>::ThrowIfRowOutOfRange(size_t row) const
{
	if (row >= m_rowCount)
		throw std::out_of_range("Row out of range");
}

template<typename T>
inline void Matrix<T>::ThrowIfColumnOutOfRange(size_t column) const
{
	if (column >= m_columnCount)
		throw std::out_of_range("Column out of range");
}

template<typename T>
inline void Matrix<T>::AssertNoOverflow() const
{
	if (m_columnCount != 0 && m_length / m_columnCount != m_rowCount)
		throw std::overflow_error("");
}