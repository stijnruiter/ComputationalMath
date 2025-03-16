#include "Renderer.hpp"

#include <glad/glad.h>
#include "../Debug/gl_debug.hpp"

#include "Render/Shader/SolidColorShader.hpp"

Renderer::Renderer()
    : m_solidColorShader("SOLID_COLOR_SHADER")
{
    m_solidColorShader.Create(SolidColorShader::GLSL_SHADER_VERTEX, SolidColorShader::GLSL_SHADER_FRAGMENT);
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


void Renderer::UpdateCamera(const CameraTransformation &transformation)
{
    m_solidColorShader.SetUniformMatrix4("model", transformation.Model, true);
    m_solidColorShader.SetUniformMatrix4("view", transformation.View, true);
    m_solidColorShader.SetUniformMatrix4("projection", transformation.Projection, true);
}

void Renderer::SetLineWidth(float width)
{
    GLCHECK(glLineWidth(width));
}

void Renderer::EnableLinearAlphaBlend() 
{
    GLCHECK(glEnable(GL_BLEND));
    GLCHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void Renderer::DisableAlphaBlend() 
{
    GLCHECK(glDisable(GL_BLEND));
}

void Renderer::EnableDepth() 
{    
    GLCHECK(glEnable(GL_DEPTH_TEST));
}

void Renderer::DisableDepth()
{
    GLCHECK(glDisable(GL_DEPTH_TEST));
}

void Renderer::UseSolidColor(float r, float g, float b, float a)
{
    m_solidColorShader.Use();
    m_solidColorShader.SetUniformVector4("drawColor", glm::vec4(r, g, b, a));
}