#pragma once

#include <Geometry/Structures/PlanarStraightLineGraph.hpp>

#include <Render/Core/IndexBuffer.hpp>
#include <Render/Core/VertexArrayObject.hpp>
#include <Render/Core/VertexBuffer.hpp>
#include <Render/Drawable/DrawableObject.hpp>

#include <memory>

class DrawableGraph : public DrawableObject
{
public:
    DrawableGraph(const Geometry::PlanarStraightLineGraph& graph);
    virtual void Draw(Renderer& render) override;

private:
    std::unique_ptr<VertexArrayObject> m_vao;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;
    std::unique_ptr<IndexBuffer<Geometry::LineElement>> m_triangleBuffer;
};