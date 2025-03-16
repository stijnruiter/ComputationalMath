#pragma once
#include <Render/Drawable/DrawableObject.hpp>
#include <Render/Core/VertexArrayObject.hpp>
#include <Render/Core/VertexBuffer.hpp>
#include <Render/Core/IndexBuffer.hpp>

#include <memory>

class Axis : public DrawableObject
{
public:
    Axis();
    virtual void Draw(Renderer& render) override;

private:
    std::unique_ptr<VertexArrayObject> m_vao;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;
    std::unique_ptr<IndexBuffer<unsigned int>> m_indexBuffer;
};