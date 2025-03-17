#include "DrawableGraph.hpp"

#include "DrawableMesh.hpp"

DrawableGraph::DrawableGraph(const Geometry::PlanarStraightLineGraph& graph)
{
    std::vector<float> zvalues = std::vector<float>(graph.GetVertexCount());
    std::vector<Geometry::Vertex3F> vertices = DrawableMesh::ToVertex3F(graph.GetVertices(), zvalues);

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
