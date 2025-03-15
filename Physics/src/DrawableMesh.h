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
    static std::vector<unsigned int> ToInteriorEdges(const std::vector<Geometry::TriangleElement>& elements);
    static std::vector<unsigned int> ToInteriorElements(const std::vector<Geometry::TriangleElement>& elements);
    DrawableMesh(const Geometry::Mesh2D& mesh);
    virtual void Draw(Renderer& render) override;

private:
    std::unique_ptr<VertexArrayObject> m_vao;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;
    std::unique_ptr<IndexBuffer> m_triangleBuffer;
    std::unique_ptr<IndexBuffer> m_interiorEdgeBuffer;
    std::unique_ptr<IndexBuffer> m_boundaryEdgeBuffer;
};