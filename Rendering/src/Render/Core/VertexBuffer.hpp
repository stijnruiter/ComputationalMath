#pragma once

#include <array>
#include <glad\glad.h>
#include <vector>

struct AttributeDefinition
{
public:
    int Location;
    GLenum Type;
    unsigned int Count;
    unsigned int Size;
    bool Normalized;

public:
    AttributeDefinition(const int Location, const GLenum& Type, const unsigned int Count, const unsigned int Size, const bool Normalized)
        : Location(Location), Type(Type), Count(Count), Size(Size), Normalized(Normalized) {}
};

class VertexBuffer
{
private:
    unsigned int m_bufferId;
    unsigned int m_stride;
    std::vector<AttributeDefinition> m_attributes;

public:
    VertexBuffer(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW);

    template <typename T>
    VertexBuffer(const std::vector<T>& vector, GLenum usage = GL_STATIC_DRAW);

    template <typename T, std::size_t N>
    VertexBuffer(const std::array<T, N>& array, GLenum usage = GL_STATIC_DRAW);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

    void DefineFloatAttribute(const int shaderLocation, const unsigned int count);

    std::vector<AttributeDefinition> GetAttributes() const;
    unsigned int GetStride() const;

    void SetData(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW);
};

template <typename T>
inline VertexBuffer::VertexBuffer(const std::vector<T>& vector, GLenum usage)
    : VertexBuffer(&vector[0], vector.size() * sizeof(T), usage)
{
}

template <typename T, std::size_t N>
inline VertexBuffer::VertexBuffer(const std::array<T, N>& array, GLenum usage)
    : VertexBuffer(&array[0], array.size() * sizeof(T), usage)
{
}
