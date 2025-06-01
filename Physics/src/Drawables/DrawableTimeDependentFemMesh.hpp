#pragma once
#include "Drawables/DrawableMesh.hpp"
#include "Fem/HeatEquationWithoutSource.hpp"

class DrawableTimeDependentFemMesh : public DrawableMesh
{
private:
    HeatEquationWithoutSource m_femProblem;

public:
    explicit DrawableTimeDependentFemMesh(const HeatEquationWithoutSource& fem);

    void Update(float deltaTime) override;

    void UpdateValues();
};
