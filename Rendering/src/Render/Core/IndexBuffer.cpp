#include "IndexBuffer.hpp"

#include "../Debug/gl_debug.hpp"

IndexBuffer::IndexBuffer(const unsigned int* indices, const size_t count, GLenum usage)
{
    this->m_count = count;
    GLCHECK(glGenBuffers(1, &m_bufferId));
    GLCHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId));
    GLCHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, usage));

}

IndexBuffer::~IndexBuffer()
{
    GLCHECK(glDeleteBuffers(1, &m_bufferId));
    m_bufferId = 0;
    m_count = 0;
}

void IndexBuffer::Bind() const
{
    GLCHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId));
}

void IndexBuffer::Unbind() const
{
    GLCHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

size_t IndexBuffer::GetCount() const
{
    return this->m_count;
}
