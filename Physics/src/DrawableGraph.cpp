#include "DrawableGraph.h"

#include "DrawableMesh.h"

DrawableGraph::DrawableGraph(const Geometry::PlanarStraightLineGraph &graph)
{
    std::vector<Geometry::Vertex3F> vertices = DrawableMesh::ToVertex3F(graph.GetVertices());
    std::vector<unsigned int> elements;
    for(auto& line : graph.GetLineSegments())
    {
        elements.push_back(line.I);
        elements.push_back(line.J);
    }

    m_vao = std::make_unique<VertexArrayObject>();
    m_vao->Bind();

    m_vertexBuffer = std::make_unique<VertexBuffer>(&vertices[0], vertices.size() * sizeof(Geometry::Vertex3F));
    m_vertexBuffer->DefineFloatAttribute(0, 3);
    m_vao->AddBuffer(*m_vertexBuffer);

    m_triangleBuffer = std::make_unique<IndexBuffer>(&elements[0], elements.size());
}

void DrawableGraph::Draw(Renderer &render)
{
    m_vao->Bind();
    render.EnableLinearAlphaBlend();

    render.UseSolidColor(1, 0, 0);
    render.DrawLines(*m_triangleBuffer);
}
