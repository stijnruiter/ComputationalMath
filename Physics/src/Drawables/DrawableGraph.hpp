#pragma once

#include <Geometry/Structures/PlanarStraightLineGraph.hpp>

#include <Render/Core/IndexBuffer.hpp>
#include <Render/Core/VertexArrayObject.hpp>
#include <Render/Core/VertexBuffer.hpp>
#include <Render/Drawable/DrawableObject.hpp>

#include <memory>

class DrawableGraph : public Render::DrawableObject
{
public:
    DrawableGraph(const Geometry::PlanarStraightLineGraph& graph);
    void Draw(Render::Renderer& render) override;

private:
    std::unique_ptr<Render::VertexArrayObject> m_vao;
    std::unique_ptr<Render::VertexBuffer> m_vertexBuffer;
    std::unique_ptr<Render::IndexBuffer<Geometry::LineElement>> m_triangleBuffer;
};