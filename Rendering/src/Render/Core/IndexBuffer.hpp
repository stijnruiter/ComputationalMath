#pragma once

#include "../Debug/gl_debug.hpp"
#include <array>
#include <glad\glad.h>
#include <vector>

namespace Render
{
    template <typename T>
    class IndexBuffer
    {
    private:
        GLuint m_bufferId;
        size_t m_count;

    public:
        IndexBuffer(const T* indices, const size_t count, GLenum usage = GL_STATIC_DRAW);
        IndexBuffer(const std::vector<T>& indices, GLenum usage = GL_STATIC_DRAW);

        template <std::size_t N>
        IndexBuffer(const std::array<T, N>& indices, GLenum usage = GL_STATIC_DRAW);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;

        size_t GetCount() const;
        GLsizei GetPrimitiveSize() const;
    };

    template <typename T>
    IndexBuffer<T>::IndexBuffer(const T* indices, const size_t count, GLenum usage)
    {
        this->m_count = count;
        GLCHECK(glGenBuffers(1, &m_bufferId));
        GLCHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId));
        GLCHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(T), indices, usage));
    }

    template <typename T>
    IndexBuffer<T>::IndexBuffer(const std::vector<T>& indices, GLenum usage)
        : IndexBuffer<T>(&indices[0], indices.size(), usage)
    {
    }

    template <typename T>
    template <typename std::size_t N>
    inline IndexBuffer<T>::IndexBuffer(const std::array<T, N>& indices, GLenum usage)
        : IndexBuffer<T>(&indices[0], indices.size(), usage)
    {
    }

    template <typename T>
    IndexBuffer<T>::~IndexBuffer()
    {
        GLCHECK(glDeleteBuffers(1, &m_bufferId));
        m_bufferId = 0;
        m_count = 0;
    }

    template <typename T>
    void IndexBuffer<T>::Bind() const
    {
        GLCHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId));
    }

    template <typename T>
    void IndexBuffer<T>::Unbind() const
    {
        GLCHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    template <typename T>
    size_t IndexBuffer<T>::GetCount() const
    {
        return this->m_count;
    }

    template <typename T>
    GLsizei IndexBuffer<T>::GetPrimitiveSize() const
    {
        return m_count * sizeof(T) / sizeof(GLuint);
    }
}