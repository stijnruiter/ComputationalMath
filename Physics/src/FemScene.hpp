#pragma once

#include "Drawables/Axis.hpp"
#include "Drawables/DrawableMesh.hpp"
#include "Drawables/DrawableTimeDependentFemMesh.hpp"
#include <Geometry/MeshGenerator.hpp>
#include <Geometry/Structures/Rectangle.hpp>
#include <Render/Drawable/ObjectScene.hpp>
#include <algorithm>

template <typename T, typename... _Args>
std::unique_ptr<Render::ObjectScene> CreateFemScene(_Args&&... __args)
{
    using namespace Geometry;
    Rectangle bounds(-0.75f, 0.75f, -0.75f, 0.75f);
    Mesh2D mesh = CreateRectangularMesh(bounds, 10, 10);
    T fem(bounds, mesh, std::forward<_Args>(__args)...);
    LinearAlgebra::ColumnVector<float> solution = fem.Solve();

    auto scene = std::make_unique<Render::ObjectScene>(true);
    scene->AddObject(std::make_unique<DrawableMesh>(mesh, solution));
    scene->AddObject(std::make_unique<Axis>());
    return scene;
}

template <typename T, typename... _Args>
std::unique_ptr<Render::ObjectScene> CreateTimeFemScene(_Args&&... __args)
{
    using namespace Geometry;

    const Rectangle bounds(-0.75f, 0.75f, -0.75f, 0.75f);
    Mesh2D mesh = CreateRectangularMesh(bounds, 25, 25);
    T fem(mesh, std::forward<_Args>(__args)...);
    auto scene = std::make_unique<Render::ObjectScene>(true);
    auto drawableFem = std::make_unique<DrawableTimeDependentFemMesh>(fem);
    scene->AddObject(std::move(drawableFem));
    scene->AddObject(std::make_unique<Axis>());
    return scene;
}