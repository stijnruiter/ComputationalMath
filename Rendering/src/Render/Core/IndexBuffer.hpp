#pragma once

#include <glad\glad.h>

class IndexBuffer
{
private:
	unsigned int m_bufferId;
	size_t m_count;

public:
	IndexBuffer(const unsigned int* indices, const size_t count, GLenum usage = GL_STATIC_DRAW);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	size_t GetCount() const;
};