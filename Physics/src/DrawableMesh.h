#pragma once

#include <Geometry/Structures/Mesh2D.h>

#include <Render/Drawable/DrawableObject.hpp>
#include <Render/Core/VertexArrayObject.hpp>
#include <Render/Core/VertexBuffer.hpp>
#include <Render/Core/IndexBuffer.hpp>

#include <memory>

class DrawableMesh : public DrawableObject
{
public:
    static std::vector<Geometry::Vertex3F> ToVertex3F(const std::vector<Geometry::Vertex2F>& vertices);
    DrawableMesh(const Geometry::Mesh2D& mesh);
    virtual void Draw(Renderer& render) override;

private:
    std::unique_ptr<VertexArrayObject> m_vao;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;
    std::unique_ptr<VertexBuffer> m_valuesBuffer;
    std::unique_ptr<IndexBuffer<Geometry::TriangleElement>> m_triangleBuffer;
    std::unique_ptr<IndexBuffer<Geometry::LineElement>> m_interiorEdgeBuffer;
    std::unique_ptr<IndexBuffer<Geometry::LineElement>> m_boundaryEdgeBuffer;
};