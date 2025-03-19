#pragma once

#include <Geometry/Structures/Mesh2D.hpp>
#include <LinearAlgebra/VectorBase.hpp>

#include <Render/Core/IndexBuffer.hpp>
#include <Render/Core/VertexArrayObject.hpp>
#include <Render/Core/VertexBuffer.hpp>
#include <Render/Drawable/DrawableObject.hpp>

#include <memory>

class DrawableMesh : public DrawableObject
{
public:
    DrawableMesh(const Geometry::Mesh2D& mesh);
    DrawableMesh(const Geometry::Mesh2D& mesh, const std::vector<float>& values);
    DrawableMesh(const Geometry::Mesh2D& mesh, const ColumnVector<float>& values);
    DrawableMesh(const Geometry::Mesh2D& mesh, const float* values, size_t length);
    virtual void Draw(Renderer& render) override;

protected:
    static std::vector<Geometry::Vertex3F> ToVertex3F(const std::vector<Geometry::Vertex2F>& vertices, const float* zValues);
    static std::vector<float> NormalizeData(const float* data, size_t length);
    std::unique_ptr<VertexArrayObject> m_vao;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;
    std::unique_ptr<VertexBuffer> m_valuesBuffer;
    std::unique_ptr<IndexBuffer<Geometry::TriangleElement>> m_triangleBuffer;
    std::unique_ptr<IndexBuffer<Geometry::LineElement>> m_interiorEdgeBuffer;
    std::unique_ptr<IndexBuffer<Geometry::LineElement>> m_boundaryEdgeBuffer;
};