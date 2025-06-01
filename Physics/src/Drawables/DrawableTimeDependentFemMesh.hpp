#pragma once
#include "Drawables/DrawableMesh.hpp"
#include "Fem/HeatEquationWithoutSource.hpp"

class DrawableTimeDependentFemMesh : public DrawableMesh
{

public:
    explicit DrawableTimeDependentFemMesh(const HeatEquationWithoutSource& fem);

    void Update(float deltaTime) override;

    void UpdateValues();

private:
    HeatEquationWithoutSource m_femProblem;
};
