#include "Renderer.hpp"

#include <glad/glad.h>
#include "../Debug/gl_debug.hpp"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::SetClearColor(float red, float green, float blue, float alpha)
{
	GLCHECK(glClearColor(red, green, blue, alpha));
}

void Renderer::Clear()
{
	GLCHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArrayObject& vao, const IndexBuffer& elements, const ShaderProgram& program)
{
    program.Use();
    vao.Bind();
    GLCHECK(glDrawElements(GL_TRIANGLES, (GLsizei)elements.GetCount(), GL_UNSIGNED_INT, NULL));
}
