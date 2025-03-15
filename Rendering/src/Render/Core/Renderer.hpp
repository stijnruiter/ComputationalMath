#pragma once

#include "ShaderProgram.hpp"
#include "IndexBuffer.hpp"
#include "VertexArrayObject.hpp"
#include "CameraTransformation.hpp"

class Renderer
{
private:
	ShaderProgram m_solidColorShader;
public:
	Renderer();
	~Renderer();
	void SetClearColor(float r, float g, float b, float a = 1.0f);
	void Clear();
	void Draw(const VertexArrayObject& vao, const IndexBuffer& elements, const ShaderProgram& program);

	void SetLineWidth(float width);
	void EnableLinearAlphaBlend();
	void DisableAlphaBlend();

	void EnableDepth();
	void DisableDepth();

	void UseSolidColor(float r, float g, float b, float a = 1.0f);

	void DrawLines(const IndexBuffer& elements);
	void DrawElements(const IndexBuffer& elements);

	void UpdateCamera(const CameraTransformation& transformation);
};