#pragma once
#include "Drawables/DrawableMesh.hpp"
#include "Fem/HeatEquationWithoutSource.hpp"

class DrawableTimeDependentFemMesh : public DrawableMesh
{
private:
    HeatEquationWithoutSource m_femProblem;

public:
    DrawableTimeDependentFemMesh(const HeatEquationWithoutSource& fem);

    virtual void Update(float deltaTime) override;

    void UpdateValues();
};
