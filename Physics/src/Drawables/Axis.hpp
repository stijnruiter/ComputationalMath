#pragma once
#include <Geometry/Structures/SimplexElements.hpp>
#include <Render/Core/IndexBuffer.hpp>
#include <Render/Core/VertexArrayObject.hpp>
#include <Render/Core/VertexBuffer.hpp>
#include <Render/Drawable/DrawableObject.hpp>

#include <memory>

class Axis : public DrawableObject
{
public:
    Axis();
    virtual void Draw(Renderer& render) override;

private:
    std::unique_ptr<VertexArrayObject> m_vao;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;
    std::unique_ptr<VertexBuffer> m_colorBuffer;
    std::unique_ptr<IndexBuffer<Geometry::LineElement>> m_indexBuffer;
};