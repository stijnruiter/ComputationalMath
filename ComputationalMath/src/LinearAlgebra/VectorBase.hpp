#pragma once
#include <algorithm>
#include <initializer_list>
#include <memory>
#include <numeric>
#include <span>
#include <stdexcept>
#include <vector>

#include <iostream>

namespace LinearAlgebra
{
    template <typename T>
    class VectorBase;

    template <typename T>
    class VectorIterator;

    template <typename T>
    class RowVector;

    template <typename T>
    class ColumnVector : public VectorBase<T>
    {
        using VectorBase<T>::VectorBase;

    public:
        bool ElementwiseEquals(const ColumnVector& vector) const;
        bool ElementwiseCompare(const ColumnVector& vector, float epsilon) const;
        ColumnVector operator+(const ColumnVector& vector) const;
        ColumnVector operator-(const ColumnVector& vector) const;
        ColumnVector operator*(const T& scalar) const;
        friend ColumnVector<T> operator*(const T& scalar, const ColumnVector& vector) { return vector * scalar; }
        // Matrix<T> operator*(const RowVector<T>& vector) const;

        RowVector<T> Transposed() const;
    };

    template <typename T>
    class RowVector : public VectorBase<T>
    {
        using VectorBase<T>::VectorBase;

    public:
        bool ElementwiseEquals(const RowVector& vector) const;
        bool ElementwiseCompare(const RowVector& vector, float epsilon) const;

        RowVector operator+(const RowVector& vector) const;
        RowVector operator-(const RowVector& vector) const;
        RowVector operator*(const T& scalar) const;
        friend RowVector operator*(const T& scalar, const RowVector& vector) { return vector * scalar; };
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
        explicit VectorBase(size_t length);
        explicit VectorBase(std::span<T> data);
        explicit VectorBase(const std::vector<T>& data);
        VectorBase(const std::initializer_list<T>& values);

        T* Data();
        const T* Data() const;
        void Fill(const T& value);

        friend class VectorIterator<T>;

        VectorIterator<T> begin() { return VectorIterator(*this, 0); }
        VectorIterator<T> end() { return VectorIterator(*this, m_length); }

        std::span<T> AsSpan();
        std::span<T> AsSpan() const;

    protected:
        void
        ThrowIfOutOfRange(size_t index) const;
        void ThrowIfDimensionsMismatch(size_t otherLength) const;

    void ElementwiseSumVector(const VectorBase& other, VectorBase& result) const;
    void ElementwiseSubtractVector(const VectorBase& other, VectorBase& result) const;

    protected:
        std::shared_ptr<T[]> m_data;
        size_t m_length;
    };

    template <typename T>
    class VectorIterator
    {
    public:
        VectorIterator(VectorBase<T>& vector, const int start)
            : m_vector(vector), i(start) {};

        VectorIterator& operator++()
        {
            ++i;
            return *this;
        }
        T& operator*() { return m_vector[i]; }

        bool operator!=(const VectorIterator& other) { return i != other.i; }

    private:
        VectorBase<T> m_vector;
        size_t i;
    };

    template <typename T>
    T& VectorBase<T>::operator[](const size_t index)
    {
        return m_data.get()[index];
    }

    template <typename T>
    const T& VectorBase<T>::operator[](const size_t index) const
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
    size_t VectorBase<T>::GetLength() const
    {
        return m_length;
    }

    template <typename T>
    T& VectorBase<T>::GetValue(size_t index) const
    {
        ThrowIfOutOfRange(index);
        return m_data.get()[index];
    }

    template <typename T>
    void VectorBase<T>::SetValue(size_t index, const T& value)
    {
        ThrowIfOutOfRange(index);
        m_data.get()[index] = value;
    }

    template <typename T>
    VectorBase<T>::VectorBase() : m_length(0)
    {
        m_data.reset();
    }

    template <typename T>
    VectorBase<T>::VectorBase(const size_t length) : m_length(length)
    {
        m_data.reset(new T[m_length]);
    }

    template <typename T>
    VectorBase<T>::VectorBase(std::span<T> data) : VectorBase(data.size())
    {
        T* storageDestination = m_data.get();
        std::copy(data.begin(), data.end(), storageDestination);
    }

    template <typename T>
    VectorBase<T>::VectorBase(const std::vector<T>& data) : VectorBase(data.size())
    {
        T* storageDestination = m_data.get();
        std::copy(data.begin(), data.end(), storageDestination);
    }

    template <typename T>
    VectorBase<T>::VectorBase(const std::initializer_list<T>& values) : VectorBase(values.size())
    {
        T* storageDestination = m_data.get();
        std::copy(values.begin(), values.end(), storageDestination);
    }

    template <typename T>
    T* VectorBase<T>::Data()
    {
        return m_data.get();
    }

    template <typename T>
    const T* VectorBase<T>::Data() const
    {
        return m_data.get();
    }

    template <typename T>
    void VectorBase<T>::Fill(const T& value)
    {
        T* storageDestination = this->m_data.get();
        std::fill(storageDestination, storageDestination + this->m_length, value);
    }

    template <typename T>
    std::span<T> VectorBase<T>::AsSpan()
    {
        return std::span<T>{m_data.get(), m_length};
    }

    template <typename T>
    std::span<T> VectorBase<T>::AsSpan() const
    {
        return std::span<T>{m_data.get(), m_length};
    }

    template <typename T>
    void VectorBase<T>::ThrowIfOutOfRange(const size_t index) const
    {
        if (index >= m_length)
            throw std::out_of_range("Out of range");
    }

    template <typename T>
    void VectorBase<T>::ThrowIfDimensionsMismatch(const size_t otherLength) const
    {
        if (m_length != otherLength)
            throw std::invalid_argument("Dimensions mismatch");
    }

    template <typename T>
    void VectorBase<T>::ElementwiseSumVector(const VectorBase& other, VectorBase& result) const
    {
        T* resultPointer = result.m_data.get();
        T* lhs = this->m_data.get();
        T* rhs = other.m_data.get();
        std::transform(lhs, lhs + m_length, rhs, resultPointer, [](T& left, T& right)
                       { return left + right; });
    }

    template <typename T>
    void VectorBase<T>::ElementwiseSubtractVector(const VectorBase& other, VectorBase& result) const
    {
        T* resultPointer = result.m_data.get();
        T* lhs = this->m_data.get();
        T* rhs = other.m_data.get();
        std::transform(lhs, lhs + m_length, rhs, resultPointer, [](T& left, T& right)
                       { return left - right; });
    }

    template <typename T>
    bool ColumnVector<T>::ElementwiseEquals(const ColumnVector& vector) const
    {
        T* lhs = this->m_data.get();
        T* rhs = vector.m_data.get();
        return std::equal(lhs, lhs + this->m_length, rhs);
    }

    template <typename T>
    bool ColumnVector<T>::ElementwiseCompare(const ColumnVector& vector, float epsilon) const
    {
        T* lhs = this->m_data.get();
        T* rhs = vector.m_data.get();
        return std::equal(lhs, lhs + this->m_length, rhs, [epsilon](T& left, T& right)
                          { return std::abs(left - right) < epsilon; });
    }

    template <typename T>
    ColumnVector<T> ColumnVector<T>::operator+(const ColumnVector& vector) const
    {
        this->ThrowIfDimensionsMismatch(vector.m_length);
        ColumnVector result(this->m_length);
        this->ElementwiseSumVector(vector, result);
        return result;
    }

    template <typename T>
    ColumnVector<T> ColumnVector<T>::operator-(const ColumnVector& vector) const
    {
        this->ThrowIfDimensionsMismatch(vector.m_length);
        ColumnVector result(this->m_length);
        this->ElementwiseSubtractVector(vector, result);
        return result;
    }

    template <typename T>
    ColumnVector<T> ColumnVector<T>::operator*(const T& scalar) const
    {
        ColumnVector result(this->m_length);
        T* srcPtr = this->m_data.get();
        T* dstPtr = result.m_data.get();
        std::transform(srcPtr, srcPtr + this->m_length, dstPtr, [&scalar](T& right)
                       { return scalar * right; });
        return result;
    }

    template <typename T>
    RowVector<T> ColumnVector<T>::Transposed() const
    {
        // TODO: view
        return RowVector<T>(this->AsSpan());
    }

    template <typename T>
    bool RowVector<T>::ElementwiseEquals(const RowVector& vector) const
    {
        T* lhs = this->m_data.get();
        T* rhs = vector.m_data.get();
        return std::equal(lhs, lhs + this->m_length, rhs);
    }

    template <typename T>
    bool RowVector<T>::ElementwiseCompare(const RowVector& vector, float epsilon) const
    {
        T* lhs = this->m_data.get();
        T* rhs = vector.m_data.get();
        return std::equal(lhs, lhs + this->m_length, rhs, [epsilon](T& left, T& right)
                          { return std::abs(left - right) < epsilon; });
    }

    template <typename T>
    RowVector<T> RowVector<T>::operator+(const RowVector& vector) const
    {
        this->ThrowIfDimensionsMismatch(vector.m_length);
        RowVector result(this->m_length);
        this->ElementwiseSumVector(vector, result);
        return result;
    }

    template <typename T>
    RowVector<T> RowVector<T>::operator-(const RowVector& vector) const
    {
        this->ThrowIfDimensionsMismatch(vector.m_length);
        RowVector result(this->m_length);
        this->ElementwiseSubtractVector(vector, result);
        return result;
    }

    template <typename T>
    RowVector<T> RowVector<T>::operator*(const T& scalar) const
    {
        RowVector result(this->m_length);
        T* srcPtr = this->m_data.get();
        T* dstPtr = result.m_data.get();
        std::transform(srcPtr, srcPtr + this->m_length, dstPtr, [&scalar](T& right)
                       { return scalar * right; });
        return result;
    }

    template <typename T>
    T RowVector<T>::operator*(const ColumnVector<T>& vector) const
    {
        this->ThrowIfDimensionsMismatch(vector.GetLength());
        T* lhsPtr = this->m_data.get();
        const T* rhsPtr = vector.Data();
        return std::inner_product(lhsPtr, lhsPtr + this->m_length, rhsPtr, 0.0f);
    }

    template <typename T>
    ColumnVector<T> RowVector<T>::Transposed() const
    {
        // TODO: view
        return ColumnVector<T>(this->AsSpan());
    }

}