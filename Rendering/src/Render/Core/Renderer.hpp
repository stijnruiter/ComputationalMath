#pragma once

#include "CameraTransformation.hpp"
#include "IndexBuffer.hpp"
#include "ShaderProgram.hpp"
#include "VertexArrayObject.hpp"

namespace Render
{
    class Renderer
    {
    public:
        Renderer();
        ~Renderer();
        void SetClearColor(float r, float g, float b, float a = 1.0f);
        void Clear();

        void SetLineWidth(float width);
        void EnableLinearAlphaBlend();
        void DisableAlphaBlend();

        void EnableDepth();
        void DisableDepth();

        void UseSolidColor(float r, float g, float b, float a = 1.0f);
        void UseVertexColor();
        void UseScalarColor();

        template <typename T>
        void Draw(const VertexArrayObject& vao, const IndexBuffer<T>& elements, const ShaderProgram& program);

        template <typename T>
        void DrawLines(const IndexBuffer<T>& elements);

        template <typename T>
        void DrawElements(const IndexBuffer<T>& elements);

        void UpdateCamera(const CameraTransformation& transformation);

    private:
        ShaderProgram m_solidColorShader;
        ShaderProgram m_vertexColorShader;
        ShaderProgram m_scalarColorShader;
    };

    template <typename T>
    // ReSharper disable once CppMemberFunctionMayBeStatic
    void Renderer::Draw(const VertexArrayObject& vao, const IndexBuffer<T>& elements, const ShaderProgram& program)
    {
        program.Use();
        vao.Bind();

        GLCHECK(glDrawElements(GL_TRIANGLES, elements.GetPrimitiveSize(), GL_UNSIGNED_INT, NULL));
    }

    template <typename T>
    // ReSharper disable once CppMemberFunctionMayBeStatic
    void Renderer::DrawLines(const IndexBuffer<T>& elements)
    {
        elements.Bind();
        GLCHECK(glDrawElements(GL_LINES, elements.GetPrimitiveSize(), GL_UNSIGNED_INT, NULL));
    }

    template <typename T>
    // ReSharper disable once CppMemberFunctionMayBeStatic
    void Renderer::DrawElements(const IndexBuffer<T>& elements)
    {
        elements.Bind();
        GLCHECK(glDrawElements(GL_TRIANGLES, elements.GetPrimitiveSize(), GL_UNSIGNED_INT, NULL));
    }
}