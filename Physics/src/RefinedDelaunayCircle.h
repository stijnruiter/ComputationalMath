#pragma once

#include <Geometry/RefinedDelaunay.hpp>
#include <Geometry/Structures/PlanarStraightLineGraph.hpp>
#include <Render/Drawable/ObjectScene.hpp>
#include <memory>

#include "Drawables/Axis.hpp"
#include "Drawables/DrawableGraph.hpp"
#include "Drawables/DrawableMesh.hpp"
#include <Geometry/MeshGenerator.hpp>

Geometry::PlanarStraightLineGraph CreateGraph()
{
    std::vector<Geometry::Vertex2F> vertices = {
        {-0.822222222f, 0.862222222f},
        {0.257777778f, 0.76f},
        {0.057777778f, 0.053333333f},
        {0.333333333f, -0.235555556f},
        {0.502222222f, 0.626666667f},
        {0.764444444f, -0.075555556f},
        {0.466666667f, -0.791111111f},
        {0.155555556f, -0.871111111f},
        {-0.177777778f, -0.866666667f},
        {-0.497777778f, -0.684444444f},
        {0.04f, -0.457777778f},
        {0.022222222f, -0.395555556f},
        {-0.773333333f, -0.035555556f},
    };
    Geometry::PlanarStraightLineGraph graph;
    graph.AddClosedLineSegments(vertices);
    graph.AddLineSegments({{-0.6f, 0.5f},
                           {-0.5f, 0.5f},
                           {-0.3f, 0.3f}});
    return graph;
}

std::unique_ptr<DrawableMesh> CreateRefinedDelaunay(const Geometry::PlanarStraightLineGraph& graph)
{
    Geometry::RefinedDelaunay delaunayMesh = Geometry::RefinedDelaunay::CreateTriangulation(graph);
    delaunayMesh.Refine(25);
    return std::make_unique<DrawableMesh>(delaunayMesh.ToMesh());
}

std::unique_ptr<ObjectScene> CreateDelaunayScene()
{
    std::unique_ptr<ObjectScene> scene = std::make_unique<ObjectScene>(false);

    Geometry::PlanarStraightLineGraph graph = CreateGraph();
    scene->AddObject(CreateRefinedDelaunay(graph));
    scene->AddObject(std::make_unique<DrawableGraph>(graph));

    scene->AddObject(std::make_unique<Axis>());
    return scene;
}
std::unique_ptr<ObjectScene> CreateCircularScene()
{
    std::unique_ptr<ObjectScene> scene = std::make_unique<ObjectScene>(false);
    scene->AddObject(std::make_unique<DrawableMesh>(Geometry::CreateCircularMesh(0, 0, 0.8f, 0.1)));
    scene->AddObject(std::make_unique<Axis>());
    return scene;
}