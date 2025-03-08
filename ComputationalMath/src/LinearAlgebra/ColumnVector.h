#pragma once
#include <memory>

template <class T>
class ColumnVector
{
public:
	ColumnVector();
	ColumnVector(size_t rows);
	ColumnVector(size_t rows, const T* data);

	T Get(size_t index) const;
	void Set(size_t index, T value);

	size_t GetLength();

private:
	std::shared_ptr<T> m_data;
	size_t m_length;
};

template<class T>
ColumnVector<T>::ColumnVector() : m_length(0)
{
	m_data.reset();
}

template<class T>
ColumnVector<T>::ColumnVector(size_t rows) : m_length(rows)
{
	m_data.reset(new T[rows]);
}

template<class T>
ColumnVector<T>::ColumnVector(size_t rows, const T* data) : ColumnVector(rows)
{
	T* destination = m_data.get();
	std::copy(data, data + rows, destination);
}

template<class T>
T ColumnVector<T>::Get(size_t index) const
{
	if (index >= m_length)
		throw std::out_of_range("Out of Range");

	return m_data.get()[index];
}

template<class T>
void ColumnVector<T>::Set(size_t index, T value)
{
	if (index >= m_length)
		throw std::out_of_range("Out of Range");

	m_data.get()[index] = value;
}

template<class T>
inline size_t ColumnVector<T>::GetLength()
{
	return m_length;
}
