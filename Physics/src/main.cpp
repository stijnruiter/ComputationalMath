#include <LinearAlgebra/Matrix.hpp>
#include <LinearAlgebra/VectorBase.hpp>
#include <iostream>

#include <LinearAlgebra/FactorizationLU.hpp>

#include <Geometry/RectangularMesh.hpp>
#include <Geometry/RefinedDelaunay.hpp>
#include <Geometry/Structures/Rectangle.hpp>

#include "Drawables/Axis.hpp"
#include "Drawables/DrawableGraph.hpp"
#include "Drawables/DrawableMesh.hpp"
#include <Render/Drawable/ObjectScene.hpp>
#include <Render/Window.hpp>

#include "Fem/HelmholtzEquationWithSource.hpp"
#include "Fem/LaplaceFem.hpp"

void RandomMath()
{
    Matrix<float> mat(3, 3, new float[9]{
        1, 2, 3, 
        3, 2, 1, 
        2, 1, 3
    });
    ColumnVector<float> rhs(3, new float[3]{1, 2, 2});

    LinearAlgebra::Factorization::FactorizationResult<float> factorization = LinearAlgebra::Factorization::PluFactorization(mat, 1e-5f);

    std::cout << "A = PLU = " << mat << std::endl;
    std::cout << "U = " << LinearAlgebra::Factorization::ExtractUpperMatrix(factorization.Factorization) << std::endl;
    std::cout << "L = " << LinearAlgebra::Factorization::ExtractLowerMatrix(factorization.Factorization) << std::endl;
    std::cout << "Determinant: " << LinearAlgebra::Factorization::Determinant(factorization) << std::endl;
    ColumnVector<float> result = LinearAlgebra::Factorization::LUSolve(mat, rhs, 1e-5f);
    std::cout << std::endl
              << "b = " << rhs << std::endl;
    std::cout << "A\\b = " << result << std::endl;
}

Geometry::PlanarStraightLineGraph CreateGraph()
{
    std::vector<Geometry::Vertex2F> vertices({
        Geometry::Vertex2F(-0.822222222f, 0.862222222f),
        Geometry::Vertex2F(0.257777778f, 0.76f),
        Geometry::Vertex2F(0.057777778f, 0.053333333f),
        Geometry::Vertex2F(0.333333333f, -0.235555556f),
        Geometry::Vertex2F(0.502222222f, 0.626666667f),
        Geometry::Vertex2F(0.764444444f, -0.075555556f),
        Geometry::Vertex2F(0.466666667f, -0.791111111f),
        Geometry::Vertex2F(0.155555556f, -0.871111111f),
        Geometry::Vertex2F(-0.177777778f, -0.866666667f),
        Geometry::Vertex2F(-0.497777778f, -0.684444444f),
        Geometry::Vertex2F(0.04f, -0.457777778f),
        Geometry::Vertex2F(0.022222222f, -0.395555556f),
        Geometry::Vertex2F(-0.773333333f, -0.035555556f),
    });
    Geometry::PlanarStraightLineGraph graph;
    graph.AddClosedLineSegments(vertices);
    graph.AddLineSegments(std::vector<Geometry::Vertex2F>({Geometry::Vertex2F(-0.6f, 0.5f),
                                                           Geometry::Vertex2F(-0.5f, 0.5f),
                                                           Geometry::Vertex2F(-0.3f, 0.3f)}));
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

template <typename T, typename... _Args>
typename std::enable_if<std::is_base_of<FemProblem2dBase, T>::value, std::unique_ptr<ObjectScene>>::type CreateFemScene(_Args&&... __args)
{
    using namespace Geometry;
    Rectangle bounds(-0.75f, 0.75f, -0.75f, 0.75f);
    Mesh2D mesh = CreateRectangularMesh(bounds, 10, 10);
    T fem(bounds, mesh, std::forward<_Args>(__args)...);
    ColumnVector<float> solution = fem.Solve();
    std::vector<float> solutionVector(solution.GetLength());
    for (size_t i = 0; i < solution.GetLength(); i++)
    {
        solutionVector[i] = solution[i];
    }

    std::unique_ptr<ObjectScene> scene = std::make_unique<ObjectScene>(true);
    std::unique_ptr<DrawableMesh> drawableMesh = std::make_unique<DrawableMesh>(mesh, solutionVector);

    scene->AddObject(std::move(drawableMesh));
    scene->AddObject(std::make_unique<Axis>());
    return scene;
}

int main()
{
    RandomMath();

    Window window(800, 600, "Physics");
    window.SetMouseCursor(true);

    window.AddScene(CreateDelaunayScene());
    window.AddScene(CreateFemScene<HelmholtzEquationWithSourceFEM>(5));
    window.AddScene(CreateFemScene<LaplaceFem>());
    size_t sceneIndex = 0;
    window.SetCallbackOnKey([&sceneIndex, &window](const KeyEvent& eventArgs)
                            {
        if (eventArgs.Action == GLFW_PRESS && eventArgs.Key == GLFW_KEY_1)
        {
            sceneIndex = (sceneIndex + 1) % window.GetSceneCount();
            window.SwitchScene(sceneIndex);
        } });
    window.Run();

    return 0;
}