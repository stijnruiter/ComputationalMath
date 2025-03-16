#include "Axis.h"
#include <Geometry/Structures/Vertex.h>
#include <Geometry/Structures/SimplexElements.h>

Axis::Axis()
{
    Geometry::Vertex3F vertices[] = 
    {
        Geometry::Vertex3F(-5,  0,  0), Geometry::Vertex3F(5, 0, 0),
        Geometry::Vertex3F( 0, -5,  0), Geometry::Vertex3F(0, 5, 0),
        Geometry::Vertex3F( 0,  0, -5), Geometry::Vertex3F(0, 0, 5),
    };
    // Geometry::LineElement indices[] = {
    //     Geometry::LineElement(0, 1),
    //     Geometry::LineElement(2, 3),
    //     Geometry::LineElement(4, 5)
    // };
    const unsigned int indices[] = {
        0,  1, 2, 3, 4, 5
    };

    m_vao = std::make_unique<VertexArrayObject>();
    m_vao->Bind();

    m_vertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    m_vertexBuffer->DefineFloatAttribute(0, 3);
    m_vao->AddBuffer(*m_vertexBuffer);

    m_indexBuffer = std::make_unique<IndexBuffer<unsigned int>>(indices, sizeof(indices) / sizeof(unsigned int));
}

void Axis::Draw(Renderer &render)
{
    m_vao->Bind();
    render.UseSolidColor(1.0f, 1.0f, 1.0f);
    render.SetLineWidth(4);
    render.DrawLines(*m_indexBuffer);
}
