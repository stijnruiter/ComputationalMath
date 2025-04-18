#include "DrawableGraph.hpp"

#include "DrawableMesh.hpp"

DrawableGraph::DrawableGraph(const Geometry::PlanarStraightLineGraph& graph)
{
    std::vector<Geometry::Vertex3F> vertices(graph.GetVertexCount());
    const std::vector<Geometry::Vertex2F>& oldVertices = graph.GetVertices();
    std::transform(oldVertices.begin(), oldVertices.end(), vertices.begin(),
                   [](const Geometry::Vertex2F& vertex)
                   { return vertex.XY0(); });

    m_vao = std::make_unique<VertexArrayObject>();
    m_vao->Bind();

    m_vertexBuffer = std::make_unique<VertexBuffer>(&vertices[0], vertices.size() * sizeof(Geometry::Vertex3F));
    m_vertexBuffer->DefineFloatAttribute(0, 3);
    m_vao->AddBuffer(*m_vertexBuffer);

    m_triangleBuffer = std::make_unique<IndexBuffer<Geometry::LineElement>>(graph.GetLineSegments());
}

void DrawableGraph::Draw(Renderer& render)
{
    m_vao->Bind();
    render.EnableLinearAlphaBlend();

    render.UseSolidColor(1, 0, 0, 0.5f);
    render.DrawLines(*m_triangleBuffer);
}
