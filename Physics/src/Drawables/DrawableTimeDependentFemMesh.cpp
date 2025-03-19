#include "DrawableTimeDependentFemMesh.hpp"

DrawableTimeDependentFemMesh::DrawableTimeDependentFemMesh(const HeatEquationWithoutSource& fem)
    : m_femProblem(fem), DrawableMesh(fem.GetGraph())
{
}

void DrawableTimeDependentFemMesh::Update(float deltaTime)
{
    m_femProblem.SolveNextTimeStep();
    std::cout << "Time: " << m_femProblem.CurrentTime() << "s" << std::endl;
    UpdateValues();
}

void DrawableTimeDependentFemMesh::UpdateValues()
{
    std::vector<Geometry::Vertex3F> vertices = ToVertex3F(m_femProblem.GetGraph().Vertices, m_femProblem.CurrentSolution().Data());

    m_valuesBuffer->SetData(m_femProblem.CurrentSolution().Data(), m_femProblem.CurrentSolution().GetLength() * sizeof(float));
    m_vertexBuffer->SetData(&vertices[0], vertices.size() * sizeof(Geometry::Vertex3F));
}
