#include "Renderer.hpp"

#include "../Debug/gl_debug.hpp"
#include <glad/glad.h>

#include "Render/Shader/ScalarColorShader.hpp"
#include "Render/Shader/SolidColorShader.hpp"
#include "Render/Shader/VertexColorShader.hpp"
namespace Render
{
    Renderer::Renderer()
        : m_solidColorShader("SOLID_COLOR_SHADER"), m_vertexColorShader("VERTEX_COLOR_SHADER"), m_scalarColorShader("SCALAR_COLOR_SHADER")
    {
        m_solidColorShader.Create(SolidColorShader::GLSL_SHADER_VERTEX, SolidColorShader::GLSL_SHADER_FRAGMENT);
        m_vertexColorShader.Create(VertexColorShader::GLSL_SHADER_VERTEX, VertexColorShader::GLSL_SHADER_FRAGMENT);
        m_scalarColorShader.Create(ScalarColorShader::GLSL_SHADER_VERTEX, ScalarColorShader::GLSL_SHADER_FRAGMENT);
    }

    Renderer::~Renderer()
    {
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    void Renderer::SetClearColor(const float r, const float g, const float b, const float a)
    {
        GLCHECK(glClearColor(r, g, b, a));
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    void Renderer::Clear()
    {
        GLCHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }

    void Renderer::UpdateCamera(const CameraTransformation& transformation)
    {
        m_solidColorShader.SetUniformMatrix4("model", transformation.Model, true);
        m_solidColorShader.SetUniformMatrix4("view", transformation.View, true);
        m_solidColorShader.SetUniformMatrix4("projection", transformation.Projection, true);

        m_vertexColorShader.SetUniformMatrix4("model", transformation.Model, true);
        m_vertexColorShader.SetUniformMatrix4("view", transformation.View, true);
        m_vertexColorShader.SetUniformMatrix4("projection", transformation.Projection, true);

        m_scalarColorShader.SetUniformMatrix4("model", transformation.Model, true);
        m_scalarColorShader.SetUniformMatrix4("view", transformation.View, true);
        m_scalarColorShader.SetUniformMatrix4("projection", transformation.Projection, true);
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    void Renderer::SetLineWidth(const float width)
    {
        GLCHECK(glLineWidth(width));
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    void Renderer::EnableLinearAlphaBlend()
    {
        GLCHECK(glEnable(GL_BLEND));
        GLCHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    void Renderer::DisableAlphaBlend()
    {
        GLCHECK(glDisable(GL_BLEND));
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    void Renderer::EnableDepth()
    {
        GLCHECK(glEnable(GL_DEPTH_TEST));
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    void Renderer::DisableDepth()
    {
        GLCHECK(glDisable(GL_DEPTH_TEST));
    }

    void Renderer::UseSolidColor(const float r, const float g, const float b, const float a)
    {
        m_solidColorShader.Use();
        m_solidColorShader.SetUniformVector4("drawColor", glm::vec4(r, g, b, a));
    }

    // ReSharper disable once CppMemberFunctionMayBeConst
    void Renderer::UseVertexColor()
    {
        m_vertexColorShader.Use();
    }

    // ReSharper disable once CppMemberFunctionMayBeConst
    void Renderer::UseScalarColor()
    {
        m_scalarColorShader.Use();
    }
}