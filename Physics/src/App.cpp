#include <iostream>
#include <LinearAlgebra/VectorBase.h>
#include <LinearAlgebra/Matrix.h>

#include <LinearAlgebra/FactorizationLU.h>

#include <Geometry/RefinedDelaunay.h>

#include <Render/Window.hpp>
#include <Render/Drawable/ObjectScene.hpp>
#include "Axis.h"
#include "DrawableMesh.h"
#include "DrawableGraph.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    Matrix<float> mat(3, 3, new float[9]{
        1,2,3,
        3,2,1,
        2,1,3
    });
    ColumnVector<float> rhs(3, new float[3]{1, 2,2});

    LinearAlgebra::Factorization::FactorizationResult<float> factorization = LinearAlgebra::Factorization::PluFactorization(mat, 1e-5f);

    std::cout << "A = PLU = " << mat << std::endl;
    std::cout << "U = " << LinearAlgebra::Factorization::ExtractUpperMatrix(factorization.Factorization) << std::endl;
    std::cout << "L = " << LinearAlgebra::Factorization::ExtractLowerMatrix(factorization.Factorization) << std::endl;
    std::cout << "Determinant: " << LinearAlgebra::Factorization::Determinant(factorization) << std::endl;
    ColumnVector<float> result = LinearAlgebra::Factorization::LUSolve(mat, rhs, 1e-5f);
    std::cout << std::endl << "b = " << rhs << std::endl; 
    std::cout << "A\\b = " << result << std::endl;
	Window window(800, 600, "Physics");
    window.SetMouseCursor(true);

    std::vector<Geometry::Vertex2F> vertices({
        Geometry::Vertex2F(-0.822222222f,  0.862222222f),
        Geometry::Vertex2F(0.257777778f,  0.76f),
        Geometry::Vertex2F(0.057777778f,  0.053333333f),
        Geometry::Vertex2F(0.333333333f, -0.235555556f),
        Geometry::Vertex2F(0.502222222f,  0.626666667f),
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
    graph.AddLineSegments(std::vector<Geometry::Vertex2F>({
        Geometry::Vertex2F(-0.6f, 0.5f), 
        Geometry::Vertex2F(-0.5f, 0.5f), 
        Geometry::Vertex2F(-0.3f, 0.3f)}));

    Geometry::RefinedDelaunay delaunayMesh = Geometry::RefinedDelaunay::CreateTriangulation(graph);
    delaunayMesh.Refine(20);

    std::unique_ptr<ObjectScene> scene = std::make_unique<ObjectScene>();
    scene->AddObject(std::make_unique<Axis>());
    scene->AddObject(std::make_unique<DrawableMesh>(delaunayMesh.ToMesh()));
    scene->AddObject(std::make_unique<DrawableGraph>(graph));
    window.AddScene(std::move(scene));

    window.Run();

	return 0;
}