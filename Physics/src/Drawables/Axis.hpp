#pragma once
#include <Geometry/Structures/SimplexElements.hpp>
#include <Render/Core/IndexBuffer.hpp>
#include <Render/Core/VertexArrayObject.hpp>
#include <Render/Core/VertexBuffer.hpp>
#include <Render/Drawable/DrawableObject.hpp>

#include <memory>

class Axis : public Render::DrawableObject
{
public:
    Axis();
    void Draw(Render::Renderer& render) override;

private:
    std::unique_ptr<Render::VertexArrayObject> m_vao;
    std::unique_ptr<Render::VertexBuffer> m_vertexBuffer;
    std::unique_ptr<Render::VertexBuffer> m_colorBuffer;
    std::unique_ptr<Render::IndexBuffer<Geometry::LineElement>> m_indexBuffer;
};