#include "DrawableMesh.hpp"

std::vector<Geometry::Vertex3F> DrawableMesh::ToVertex3F(
    const std::vector<Geometry::Vertex2F>& vertices, const float* zValues)
{
    std::vector<Geometry::Vertex3F> newVertices;
    newVertices.reserve(vertices.size());
    for (size_t i = 0; i < vertices.size(); i++)
    {
        newVertices.push_back(Geometry::Vertex3F(vertices[i], zValues[i]));
    }
    return newVertices;
}

std::vector<float> DrawableMesh::Normalize(const float* data, size_t length)
{
    std::vector<float> values(length);
    float minValue = 1e10f;
    float maxValue = -1e10f;
    for (size_t i = 0; i < length; i++)
    {
        minValue = minValue > data[i] ? data[i] : minValue;
        maxValue = maxValue < data[i] ? data[i] : maxValue;
    }
    for (size_t i = 0; i < length; i++)
    {
        values[i] = (data[i] - minValue) / (maxValue - minValue);
    }
    return values;
}

DrawableMesh::DrawableMesh(const Geometry::Mesh2D& mesh)
    : DrawableMesh(mesh, std::vector<float>(mesh.Vertices.size(), 0))
{
}

DrawableMesh::DrawableMesh(const Geometry::Mesh2D& mesh, const std::vector<float>& values)
    : DrawableMesh(mesh, values.data(), values.size())
{
}

DrawableMesh::DrawableMesh(const Geometry::Mesh2D& mesh, const ColumnVector<float>& values)
    : DrawableMesh(mesh, values.Data(), values.GetLength())
{
}

DrawableMesh::DrawableMesh(const Geometry::Mesh2D& mesh, const float* values, size_t length)
{
    assert(mesh.Vertices.size() == length);
    std::vector<Geometry::Vertex3F> vertices = ToVertex3F(mesh.Vertices, values);
    m_vao = std::make_unique<VertexArrayObject>();
    m_vao->Bind();

    m_vertexBuffer = std::make_unique<VertexBuffer>(vertices);
    m_vertexBuffer->DefineFloatAttribute(0, 3);
    m_vao->AddBuffer(*m_vertexBuffer);

    m_valuesBuffer = std::make_unique<VertexBuffer>(Normalize(values, mesh.Vertices.size()));
    m_valuesBuffer->DefineFloatAttribute(1, 1);
    m_vao->AddBuffer(*m_valuesBuffer);

    m_triangleBuffer = std::make_unique<IndexBuffer<Geometry::TriangleElement>>(mesh.Interior);
    m_interiorEdgeBuffer = std::make_unique<IndexBuffer<Geometry::LineElement>>(mesh.GetAllEdges());
    m_boundaryEdgeBuffer = std::make_unique<IndexBuffer<Geometry::LineElement>>(mesh.Boundary);
}

void DrawableMesh::Draw(Renderer& render)
{
    m_vao->Bind();
    render.EnableLinearAlphaBlend();

    render.UseScalarColor();
    render.DrawElements(*m_triangleBuffer);
    render.UseSolidColor(0, 0, 0, 0.5f);
    render.DrawLines(*m_interiorEdgeBuffer);
    render.UseSolidColor(0, 1.0, 0, 0.5f);
    render.DrawLines(*m_boundaryEdgeBuffer);
}