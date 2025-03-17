#include "Axis.hpp"
#include <Geometry/Structures/SimplexElements.hpp>
#include <Geometry/Structures/Vertex.hpp>

Axis::Axis()
{
    std::array<Geometry::Vertex3F, 6> vertices({
        Geometry::Vertex3F(-5, 0, 0),
        Geometry::Vertex3F(5, 0, 0),
        Geometry::Vertex3F(0, -5, 0),
        Geometry::Vertex3F(0, 5, 0),
        Geometry::Vertex3F(0, 0, -5),
        Geometry::Vertex3F(0, 0, 5),
    });

    std::array<Geometry::Vertex3F, 6> colors({
        Geometry::Vertex3F(1, 0, 0),
        Geometry::Vertex3F(1, 0, 0),
        Geometry::Vertex3F(0, 0.5f, 0),
        Geometry::Vertex3F(0, 0.5f, 0),
        Geometry::Vertex3F(0, 0, 1),
        Geometry::Vertex3F(0, 0, 1),
    });
    std::array<Geometry::LineElement, 3> indices({Geometry::LineElement(0, 1),
                                                  Geometry::LineElement(2, 3),
                                                  Geometry::LineElement(4, 5)});

    m_vao = std::make_unique<VertexArrayObject>();
    m_vao->Bind();

    m_vertexBuffer = std::make_unique<VertexBuffer>(vertices);
    m_vertexBuffer->DefineFloatAttribute(0, 3);
    m_vao->AddBuffer(*m_vertexBuffer);

    m_colorBuffer = std::make_unique<VertexBuffer>(colors);
    m_colorBuffer->DefineFloatAttribute(1, 3);
    m_vao->AddBuffer(*m_colorBuffer);

    m_indexBuffer = std::make_unique<IndexBuffer<Geometry::LineElement>>(indices);
}

void Axis::Draw(Renderer& render)
{
    m_vao->Bind();
    render.UseVertexColor();
    render.SetLineWidth(4);
    render.DrawLines(*m_indexBuffer);
}
