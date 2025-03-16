#include "DrawableMesh.h"

std::vector<Geometry::Vertex3F> DrawableMesh::ToVertex3F(const std::vector<Geometry::Vertex2F> &vertices, const std::vector<float>& zValues)
{
    assert(vertices.size() == zValues.size());
    std::vector<Geometry::Vertex3F> newVertices;
    newVertices.reserve(vertices.size());
    for(size_t i = 0; i < vertices.size(); i++)
    {
        newVertices.push_back(Geometry::Vertex3F(vertices[i], zValues[i]));
    }
    return newVertices;
}

std::vector<float> DrawableMesh::Normalize(const std::vector<float>& data)
{
    std::vector<float> values(data.size());
    float minValue = 1e10f;
    float maxValue = -1e10f;
    for(size_t i = 0; i < data.size(); i++)
    {
        minValue = minValue > data[i] ? data[i] : minValue;
        maxValue = maxValue < data[i] ? data[i] : maxValue;
    }
    for(size_t i = 0; i < data.size(); i++)
    {
        values[i] = (data[i] - minValue) / (maxValue - minValue);
    }
    return values;
}

DrawableMesh::DrawableMesh(const Geometry::Mesh2D &mesh)
    : DrawableMesh(mesh, std::vector<float>(mesh.Vertices.size()))
{
}

DrawableMesh::DrawableMesh(const Geometry::Mesh2D &mesh, const std::vector<float> &values)
{
    std::vector<Geometry::Vertex3F> vertices = ToVertex3F(mesh.Vertices, values);

    m_vao = std::make_unique<VertexArrayObject>();
    m_vao->Bind();

    m_vertexBuffer = std::make_unique<VertexBuffer>(vertices);
    m_vertexBuffer->DefineFloatAttribute(0, 3);
    m_vao->AddBuffer(*m_vertexBuffer);

    assert(values.size() == vertices.size());

    m_valuesBuffer = std::make_unique<VertexBuffer>(Normalize(values));
    m_valuesBuffer->DefineFloatAttribute(1, 1);
    m_vao->AddBuffer(*m_valuesBuffer);

    m_triangleBuffer = std::make_unique<IndexBuffer<Geometry::TriangleElement>>(mesh.Interior);
    m_interiorEdgeBuffer = std::make_unique<IndexBuffer<Geometry::LineElement>>(mesh.GetAllEdges());
    m_boundaryEdgeBuffer = std::make_unique<IndexBuffer<Geometry::LineElement>>(mesh.Boundary);
}

void DrawableMesh::Draw(Renderer &render)
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
