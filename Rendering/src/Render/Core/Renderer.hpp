#pragma once

#include "ShaderProgram.hpp"
#include "IndexBuffer.hpp"
#include "VertexArrayObject.hpp"

class Renderer
{
private:

public:
	Renderer();
	~Renderer();
	void SetClearColor(float r, float g, float b, float a = 1.0f);
	void Clear();
	void Draw(const VertexArrayObject& vao, const IndexBuffer& elements, const ShaderProgram& program);
};