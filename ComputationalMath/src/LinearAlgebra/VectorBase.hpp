#pragma once
#include <algorithm>
#include <initializer_list>
#include <memory>
#include <numeric>
#include <stdexcept>

#include <iostream>

template <typename T>
class VectorBase;

template <typename T>
class RowVector;

template <typename T>
class ColumnVector : public VectorBase<T>
{
    using VectorBase<T>::VectorBase;

public:
    bool ElementwiseEquals(const ColumnVector<T>& vector) const;
    bool ElementwiseCompare(const ColumnVector<T>& vector, float epsilon) const;
    ColumnVector<T> operator+(const ColumnVector<T>& vector) const;
    ColumnVector<T> operator-(const ColumnVector<T>& vector) const;
    ColumnVector<T> operator*(const T& scalar) const;
    friend ColumnVector<T> operator*(const T& scalar, const ColumnVector<T>& vector) { return vector * scalar; }
    // Matrix<T> operator*(const RowVector<T>& vector) const;

    RowVector<T> Transposed() const;
};

template <typename T>
class RowVector : public VectorBase<T>
{
    using VectorBase<T>::VectorBase;

public:
    bool ElementwiseEquals(const RowVector<T>& vector) const;
    bool ElementwiseCompare(const RowVector<T>& vector, float epsilon) const;

    RowVector<T> operator+(const RowVector<T>& vector) const;
    RowVector<T> operator-(const RowVector<T>& vector) const;
    RowVector<T> operator*(const T& scalar) const;
    friend RowVector<T> operator*(const T& scalar, const RowVector<T>& vector) { return vector * scalar; };
    T operator*(const ColumnVector<T>& vector) const;

    ColumnVector<T> Transposed() const;
};

template <typename T>
class VectorBase
{
public:
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    // friend std::ostream& operator << (std::ostream &out, const VectorBase<T>& e);
    size_t GetLength() const;

    T& GetValue(size_t index) const;
    void SetValue(size_t index, const T& value);

    VectorBase();
    VectorBase(size_t length);
    VectorBase(size_t length, const T* data);
    VectorBase(const std::initializer_list<T>& values);

    T* Data();
    const T* Data() const;
    void Fill(const T& value);

protected:
    void ThrowIfOutOfRange(size_t index) const;
    void ThrowIfDimensionsMismatch(size_t otherLength) const;

    void ElementwiseSumVector(const VectorBase<T>& other, VectorBase<T>& result) const;
    void ElementwiseSubtractVector(const VectorBase<T>& other, VectorBase<T>& result) const;

protected:
    std::shared_ptr<T[]> m_data;
    size_t m_length;
};

template <typename T>
inline T& VectorBase<T>::operator[](size_t index)
{
    return m_data.get()[index];
}

template <typename T>
inline const T& VectorBase<T>::operator[](size_t index) const
{
    return m_data.get()[index];
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const VectorBase<T>& e)
{
    out << "Vec" << e.GetLength();
    if (e.GetLength() == 0)
        return out << "[]";

    out << "[" << e[0];
    for (size_t i = 1; i < e.GetLength(); i++)
    {
        out << ", " << e[i];
    }
    return out << ']';
}

template <typename T>
inline size_t VectorBase<T>::GetLength() const
{
    return m_length;
}

template <typename T>
inline T& VectorBase<T>::GetValue(size_t index) const
{
    ThrowIfOutOfRange(index);
    return m_data.get()[index];
}

template <typename T>
inline void VectorBase<T>::SetValue(size_t index, const T& value)
{
    ThrowIfOutOfRange(index);
    m_data.get()[index] = value;
}

template <typename T>
inline VectorBase<T>::VectorBase() : m_length(0)
{
    m_data.reset();
}

template <typename T>
inline VectorBase<T>::VectorBase(size_t length) : m_length(length)
{
    m_data.reset(new T[m_length]);
}

template <typename T>
inline VectorBase<T>::VectorBase(size_t length, const T* data) : VectorBase<T>(length)
{
    T* storageDestination = m_data.get();
    std::copy(data, data + length, storageDestination);
}

template <typename T>
inline VectorBase<T>::VectorBase(const std::initializer_list<T>& values) : VectorBase<T>(values.size())
{
    T* storageDestination = m_data.get();
    std::copy(values.begin(), values.end(), storageDestination);
}

template <typename T>
inline T* VectorBase<T>::Data()
{
    return m_data.get();
}

template <typename T>
inline const T* VectorBase<T>::Data() const
{
    return m_data.get();
}

template <typename T>
inline void VectorBase<T>::Fill(const T& value)
{
    T* storageDestination = this->m_data.get();
    std::fill(storageDestination, storageDestination + this->m_length, value);
}

template <typename T>
inline void VectorBase<T>::ThrowIfOutOfRange(size_t index) const
{
    if (index >= m_length)
        throw std::out_of_range("Out of range");
}

template <typename T>
inline void VectorBase<T>::ThrowIfDimensionsMismatch(size_t otherLength) const
{
    if (m_length != otherLength)
        throw std::invalid_argument("Dimensions mismatch");
}

template <typename T>
inline void VectorBase<T>::ElementwiseSumVector(const VectorBase<T>& other, VectorBase<T>& result) const
{
    T* resultPointer = result.m_data.get();
    T* lhs = this->m_data.get();
    T* rhs = other.m_data.get();
    std::transform(lhs, lhs + m_length, rhs, resultPointer, [](T& left, T& right)
                   { return left + right; });
}

template <typename T>
inline void VectorBase<T>::ElementwiseSubtractVector(const VectorBase<T>& other, VectorBase<T>& result) const
{
    T* resultPointer = result.m_data.get();
    T* lhs = this->m_data.get();
    T* rhs = other.m_data.get();
    std::transform(lhs, lhs + m_length, rhs, resultPointer, [](T& left, T& right)
                   { return left - right; });
}

template <typename T>
inline bool ColumnVector<T>::ElementwiseEquals(const ColumnVector<T>& vector) const
{
    T* lhs = this->m_data.get();
    T* rhs = vector.m_data.get();
    return std::equal(lhs, lhs + this->m_length, rhs);
}

template <typename T>
inline bool ColumnVector<T>::ElementwiseCompare(const ColumnVector<T>& vector, float epsilon) const
{
    T* lhs = this->m_data.get();
    T* rhs = vector.m_data.get();
    return std::equal(lhs, lhs + this->m_length, rhs, [epsilon](T& left, T& right)
                      { return std::abs(left - right) < epsilon; });
}

template <typename T>
inline ColumnVector<T> ColumnVector<T>::operator+(const ColumnVector<T>& vector) const
{
    this->ThrowIfDimensionsMismatch(vector.m_length);
    ColumnVector<T> result(this->m_length);
    this->ElementwiseSumVector(vector, result);
    return result;
}

template <typename T>
inline ColumnVector<T> ColumnVector<T>::operator-(const ColumnVector<T>& vector) const
{
    this->ThrowIfDimensionsMismatch(vector.m_length);
    ColumnVector<T> result(this->m_length);
    this->ElementwiseSubtractVector(vector, result);
    return result;
}

template <typename T>
inline ColumnVector<T> ColumnVector<T>::operator*(const T& scalar) const
{
    ColumnVector<T> result(this->m_length);
    T* srcPtr = this->m_data.get();
    T* dstPtr = result.m_data.get();
    std::transform(srcPtr, srcPtr + this->m_length, dstPtr, [&scalar](T& right)
                   { return scalar * right; });
    return result;
}

template <typename T>
inline RowVector<T> ColumnVector<T>::Transposed() const
{
    // TODO: view
    return RowVector<T>(this->m_length, this->m_data.get());
}

template <typename T>
inline bool RowVector<T>::ElementwiseEquals(const RowVector<T>& vector) const
{
    T* lhs = this->m_data.get();
    T* rhs = vector.m_data.get();
    return std::equal(lhs, lhs + this->m_length, rhs);
}

template <typename T>
inline bool RowVector<T>::ElementwiseCompare(const RowVector<T>& vector, float epsilon) const
{
    T* lhs = this->m_data.get();
    T* rhs = vector.m_data.get();
    return std::equal(lhs, lhs + this->m_length, rhs, [epsilon](T& left, T& right)
                      { return std::abs(left - right) < epsilon; });
}

template <typename T>
inline RowVector<T> RowVector<T>::operator+(const RowVector<T>& vector) const
{
    this->ThrowIfDimensionsMismatch(vector.m_length);
    RowVector<T> result(this->m_length);
    this->ElementwiseSumVector(vector, result);
    return result;
}

template <typename T>
inline RowVector<T> RowVector<T>::operator-(const RowVector<T>& vector) const
{
    this->ThrowIfDimensionsMismatch(vector.m_length);
    RowVector<T> result(this->m_length);
    this->ElementwiseSubtractVector(vector, result);
    return result;
}

template <typename T>
inline RowVector<T> RowVector<T>::operator*(const T& scalar) const
{
    RowVector<T> result(this->m_length);
    T* srcPtr = this->m_data.get();
    T* dstPtr = result.m_data.get();
    std::transform(srcPtr, srcPtr + this->m_length, dstPtr, [&scalar](T& right)
                   { return scalar * right; });
    return result;
}

template <typename T>
inline T RowVector<T>::operator*(const ColumnVector<T>& vector) const
{
    // TODO: Vectorized version
    this->ThrowIfDimensionsMismatch(vector.GetLength());
    T* lhsPtr = this->m_data.get();
    const T* rhsPtr = vector.Data();
    T result = 0;
    for (size_t i = 0; i < this->m_length; i++)
    {
        result += lhsPtr[i] * rhsPtr[i];
    }
    return result;
}

template <typename T>
inline ColumnVector<T> RowVector<T>::Transposed() const
{
    // TODO: view
    return ColumnVector<T>(this->m_length, this->m_data.get());
}
