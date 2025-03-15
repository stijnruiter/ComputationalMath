#pragma once
#include "VertexBuffer.hpp"

class VertexArrayObject
{
private:
	unsigned int m_vertexArrayId;

public:
	VertexArrayObject();
	~VertexArrayObject();

	void Bind() const;
	void Unbind() const;

	void AddBuffer(const VertexBuffer& buffer);
};