#include "DrawableMesh.h"

std::vector<Geometry::Vertex3F> DrawableMesh::ToVertex3F(const std::vector<Geometry::Vertex2F> &vertices)
{
    std::vector<Geometry::Vertex3F> newVertices;
    newVertices.reserve(vertices.size());
    for(size_t i = 0; i < vertices.size(); i++)
    {
        const Geometry::Vertex2F& vertex = vertices[i];
        newVertices.push_back(Geometry::Vertex3F(vertex.X, vertex.Y, 0.0f));
    }
    return newVertices;
}

std::vector<unsigned int> DrawableMesh::ToInteriorEdges(const std::vector<Geometry::TriangleElement> &elements)
{
    std::vector<unsigned int> result;
    result.reserve(elements.size() * 6);
    for(const auto& element : elements)
    {
        result.push_back(element.I);
        result.push_back(element.J);
        result.push_back(element.J);
        result.push_back(element.K);
        result.push_back(element.K);
        result.push_back(element.I);
    }
    return result;
}

std::vector<unsigned int> DrawableMesh::ToInteriorElements(const std::vector<Geometry::TriangleElement> &elements)
{
    std::vector<unsigned int> result;
    result.reserve(elements.size() * 3);
    for(auto& element : elements)
    {
        result.push_back(element.I);
        result.push_back(element.J);
        result.push_back(element.K);
    }
    return result;
}

DrawableMesh::DrawableMesh(const Geometry::Mesh2D &mesh)
{
    std::vector<Geometry::Vertex3F> vertices = ToVertex3F(mesh.Vertices);
    std::vector<unsigned int> interior = ToInteriorElements(mesh.Interior);
    std::vector<unsigned int> edges = ToInteriorEdges(mesh.Interior);

    m_vao = std::make_unique<VertexArrayObject>();
    m_vao->Bind();

    m_vertexBuffer = std::make_unique<VertexBuffer>(&vertices[0], mesh.Vertices.size() * sizeof(Geometry::Vertex3F));
    m_vertexBuffer->DefineFloatAttribute(0, 3);
    m_vao->AddBuffer(*m_vertexBuffer);

    m_triangleBuffer = std::make_unique<IndexBuffer>(&interior[0], interior.size());
    m_interiorEdgeBuffer = std::make_unique<IndexBuffer>(&edges[0], edges.size());
}

void DrawableMesh::Draw(Renderer &render)
{
    m_vao->Bind();
    render.EnableLinearAlphaBlend();

    render.UseSolidColor(0.7f, 0.7f, 0.5f);
    render.DrawElements(*m_triangleBuffer);
    render.UseSolidColor(0, 0, 0);
    render.DrawLines(*m_interiorEdgeBuffer);
}
