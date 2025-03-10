#pragma once
#include <memory>
#include <algorithm>
#include <stdexcept>

template<typename T, size_t N, size_t M>
class Matrix;

template <typename T, size_t N>
using ColumnVector = Matrix<T, N, 1>;

template <typename T, size_t M>
using RowVector = Matrix<T, 1, M>;

template<typename T, size_t N, size_t M>
class Matrix
{
public:
	Matrix();
	Matrix(const T* data);

	T& GetValue(size_t row, size_t column) const;
	void SetValue(size_t row, size_t column, const T& value);

	size_t GetRowCount() const;
	size_t GetColumnCount() const;

	bool ElementwiseEquals(const Matrix<T, N, M>& mat) const;
	bool ElementwiseCompare(const Matrix<T, N, M>& mat, float epsilon) const;

	T& operator()(size_t row, size_t column) const;
	Matrix<T, N, M> operator+(const Matrix<T, N, M>& mat) const;
	Matrix<T, N, M> operator-(const Matrix<T, N, M>& mat) const;

	template<size_t K>
	Matrix<T, N, K> operator*(const Matrix<T, M, K>& mat) const;

private:
	void ThrowIfOutOfRange(size_t row, size_t column) const;
	void ThrowIfRowOutOfRange(size_t row) const;
	void ThrowIfColumnOutOfRange(size_t column) const;

private:
	static constexpr std::size_t m_length		= N * M;
	static constexpr std::size_t m_rowCount		= N;
	static constexpr std::size_t m_columnCount	= M;
	
	static_assert(M == 0 || m_length / M == N, "N*M overflow");

	std::shared_ptr<T[]> m_storage;
};

template<typename T, size_t N, size_t M>
inline Matrix<T, N, M>::Matrix()
{
	m_storage.reset(new T[m_length]);
}

template<typename T, size_t N, size_t M>
inline Matrix<T, N, M>::Matrix(const T* data) : Matrix<T, N, M>()
{
	T* destination = m_storage.get();
	std::copy(data, data + m_length, destination);
}

template<typename T, size_t N, size_t M>
inline T& Matrix<T, N, M>::GetValue(size_t row, size_t column) const
{
	ThrowIfOutOfRange(row, column);
	return m_storage.get()[row * m_columnCount + column];
}

template<typename T, size_t N, size_t M>
inline void Matrix<T, N, M>::SetValue(size_t row, size_t column, const T& value)
{
	ThrowIfOutOfRange(row, column);
	m_storage.get()[row * m_columnCount + column] = value;
}

template<typename T, size_t N, size_t M>
inline size_t Matrix<T, N, M>::GetRowCount() const
{
	return m_rowCount;
}

template<typename T, size_t N, size_t M>
inline size_t Matrix<T, N, M>::GetColumnCount() const
{
	return m_columnCount;
}

template<typename T, size_t N, size_t M>
inline bool Matrix<T, N, M>::ElementwiseEquals(const Matrix<T, N, M>& mat) const
{
	T* lhs = m_storage.get();
	T* rhs = mat.m_storage.get();
	return std::equal(lhs, lhs + m_length, rhs);
}

template<typename T, size_t N, size_t M>
inline bool Matrix<T, N, M>::ElementwiseCompare(const Matrix<T, N, M>& mat, float epsilon) const
{
	T* lhs = m_storage.get();
	T* rhs = mat.m_storage.get();
	return std::equal(lhs, lhs + m_length, rhs, [epsilon](T& left, T& right) { return std::abs(left - right) < epsilon; });
}

template<typename T, size_t N, size_t M>
inline T& Matrix<T, N, M>::operator()(size_t row, size_t column) const
{
	return GetValue(row, column);
}

template<typename T, size_t N, size_t M>
inline Matrix<T, N, M> Matrix<T, N, M>::operator+(const Matrix<T, N, M>& mat) const
{
	// TODO: SIMD
	T* lhs = m_storage.get();
	T* rhs = mat.m_storage.get();
	Matrix<T, N, M> sum;
	T* sumPointer = sum.m_storage.get();
	std::transform(lhs, lhs + m_length, rhs, sumPointer, [](T& left, T& right) {return left + right; });
	return sum;
}

template<typename T, size_t N, size_t M>
inline Matrix<T, N, M> Matrix<T, N, M>::operator-(const Matrix<T, N, M>& mat) const
{
	// TODO: SIMD
	T* lhs = m_storage.get();
	T* rhs = mat.m_storage.get();

	Matrix<T, N, M> subtract;
	T* subtractPointer = subtract.m_storage.get();
	std::transform(lhs, lhs + m_length, rhs, subtractPointer, [](T& left, T& right) {return left - right; });
	return subtract;
}

template<typename T, size_t N, size_t M>
template<size_t K>
inline Matrix<T, N, K> Matrix<T, N, M>::operator*(const Matrix<T, M, K>& mat) const
{
	// TODO: SIMD
	Matrix<T, N, K> product;
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < K; j++)
		{
			T dotProduct = 0;
			for (size_t k = 0; k < M; k++)
			{
				dotProduct += GetValue(i, k) * mat.GetValue(k, j);
			}
			product.SetValue(i, j, dotProduct);
		}
	}
	return product;
}

template<typename T, size_t N, size_t M>
inline void Matrix<T, N, M>::ThrowIfOutOfRange(size_t row, size_t column) const
{
	if (row >= m_rowCount || column >= m_columnCount)
		throw std::out_of_range("Index out of range");
}

template<typename T, size_t N, size_t M>
inline void Matrix<T, N, M>::ThrowIfRowOutOfRange(size_t row) const
{
	if (row >= m_rowCount)
		throw std::out_of_range("Row out of range");
}

template<typename T, size_t N, size_t M>
inline void Matrix<T, N, M>::ThrowIfColumnOutOfRange(size_t column) const
{
	if (column >= m_columnCount)
		throw std::out_of_range("Column out of range");
}