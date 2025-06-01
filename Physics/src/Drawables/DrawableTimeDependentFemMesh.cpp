#include "DrawableTimeDependentFemMesh.hpp"

DrawableTimeDependentFemMesh::DrawableTimeDependentFemMesh(const HeatEquationWithoutSource& fem)
    : DrawableMesh(fem.GetGraph()), m_femProblem(fem)
{
    m_femProblem.StartComputation();
}

void DrawableTimeDependentFemMesh::Update(float deltaTime)
{
    if (m_femProblem.PollNextTimeStepReady())
    {
        std::cout << "Time: " << m_femProblem.CurrentTime() << "s" << std::endl;
        UpdateValues();
    }
}

// ReSharper disable once CppMemberFunctionMayBeConst
void DrawableTimeDependentFemMesh::UpdateValues()
{
    const std::vector<Geometry::Vertex3F> vertices = ToVertex3F(m_femProblem.GetGraph().Vertices, m_femProblem.CurrentSolution().Data());

    m_valuesBuffer->SetData(m_femProblem.CurrentSolution().Data(), m_femProblem.CurrentSolution().GetLength() * sizeof(float));
    m_vertexBuffer->SetData(&vertices[0], vertices.size() * sizeof(Geometry::Vertex3F));
}
