#include "VertexBuffer.hpp"

#include "../Debug/gl_debug.hpp"

VertexBuffer::VertexBuffer(const void* data, const size_t size, const GLenum usage) 
    : m_stride(0)
{
    GLCHECK(glGenBuffers(1, &m_bufferId));
    GLCHECK(glBindBuffer(GL_ARRAY_BUFFER, m_bufferId));
    GLCHECK(glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)size, data, usage));
}

VertexBuffer::~VertexBuffer()
{
    GLCHECK(glDeleteBuffers(1, &m_bufferId));
    m_bufferId = 0;
}

void VertexBuffer::Bind() const
{
    GLCHECK(glBindBuffer(GL_ARRAY_BUFFER, m_bufferId));
}

void VertexBuffer::Unbind() const
{
    GLCHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::DefineFloatAttribute(const int shaderLocation, const unsigned int count)
{
	m_attributes.push_back(AttributeDefinition(shaderLocation, GL_FLOAT, count, count * sizeof(float), GL_FALSE));

    m_stride += count * sizeof(float);
}

std::vector<AttributeDefinition> VertexBuffer::GetAttributes() const
{
    return m_attributes;
}

unsigned int VertexBuffer::GetStride() const
{
    return m_stride;
}
