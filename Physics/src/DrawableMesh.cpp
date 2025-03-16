#include "DrawableMesh.h"

std::vector<Geometry::Vertex3F> DrawableMesh::ToVertex3F(const std::vector<Geometry::Vertex2F> &vertices)
{
    std::vector<Geometry::Vertex3F> newVertices;
    newVertices.reserve(vertices.size());
    for(size_t i = 0; i < vertices.size(); i++)
    {
        newVertices.push_back(vertices[i].XY0());
    }
    return newVertices;
}

DrawableMesh::DrawableMesh(const Geometry::Mesh2D &mesh)
{
    std::vector<Geometry::Vertex3F> vertices = ToVertex3F(mesh.Vertices);

    m_vao = std::make_unique<VertexArrayObject>();
    m_vao->Bind();

    m_vertexBuffer = std::make_unique<VertexBuffer>(&vertices[0], mesh.Vertices.size() * sizeof(Geometry::Vertex3F));
    m_vertexBuffer->DefineFloatAttribute(0, 3);
    m_vao->AddBuffer(*m_vertexBuffer);

    m_triangleBuffer = std::make_unique<IndexBuffer<Geometry::TriangleElement>>(mesh.Interior);
    m_interiorEdgeBuffer = std::make_unique<IndexBuffer<Geometry::LineElement>>(mesh.GetAllEdges());
    m_boundaryEdgeBuffer = std::make_unique<IndexBuffer<Geometry::LineElement>>(mesh.Boundary);
}

void DrawableMesh::Draw(Renderer &render)
{
    m_vao->Bind();
    render.EnableLinearAlphaBlend();

    render.UseSolidColor(0.7f, 0.7f, 0.5f);
    render.DrawElements(*m_triangleBuffer);
    render.UseSolidColor(0, 0, 0);
    render.DrawLines(*m_interiorEdgeBuffer);
    render.UseSolidColor(0, 1.0, 0);
    render.DrawLines(*m_boundaryEdgeBuffer);
}
