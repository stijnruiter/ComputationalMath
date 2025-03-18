#pragma once

#include "Drawables/Axis.hpp"
#include "Drawables/DrawableMesh.hpp"
#include "Fem/FemProblem2dBase.hpp"
#include <Geometry/RectangularMesh.hpp>
#include <Geometry/Structures/Rectangle.hpp>
#include <Render/Drawable/ObjectScene.hpp>
#include <type_traits>

template <typename T, typename... _Args>
typename std::enable_if<std::is_base_of<FemProblem2dBase, T>::value, std::unique_ptr<ObjectScene>>::type CreateFemScene(_Args&&... __args)
{
    using namespace Geometry;
    Rectangle bounds(-0.75f, 0.75f, -0.75f, 0.75f);
    Mesh2D mesh = Geometry::CreateRectangularMesh(bounds, 10, 10);
    T fem(bounds, mesh, std::forward<_Args>(__args)...);
    ColumnVector<float> solution = fem.Solve();

    std::unique_ptr<ObjectScene> scene = std::make_unique<ObjectScene>(true);
    scene->AddObject(std::make_unique<DrawableMesh>(mesh, solution));
    scene->AddObject(std::make_unique<Axis>());
    return scene;
}